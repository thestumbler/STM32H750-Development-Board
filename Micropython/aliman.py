import uos
import machine
import pyb
import utime


# Micropython doesn't have .zfill(w) function
def zfill(s, width):
  """Pads the string with leading 0's.""" 
  return '{:0>{w}}'.format(s, w=width)

def hexdump( buff ):
  """Hex dump of buffer."""
  s=[]
  for b in buff:
    s.append( zfill( hex(b)[2:], 2 ) )
  return ' '.join(s)

# Micropython doesn't have datetime support
class Timestamp:
  """Provide very basic date/time timestamps"""
  MONTHS = [ 
    'Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun',
    'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec' ]
  DAYS = [
    'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun' 
    ]
  def __init__(self, t=None, ms=0):
    if t is None: self.now()
    else: self.set(t,ms)
  def now(self):
    t = utime.time() # now
    ms = utime.ticks_ms() % 1000 # ms: milliseconds
    self.set(t, ms)
  def set(self, t, ms=0):
    self.t = t
    self.ms = ms
    self.tm = utime.localtime(self.t) # tm: time structure
  def __str__(self):
    return '  '.join([ self.time_only(), self.date_only() ])
  def __repr__(self):
    return self.__str__()
  def __sub__(a,b):
    return (a.t + a.ms/1000.0) - (b.t + b.ms/1000.0)
  def __add__(a,b):
    return (a.t + a.ms/1000.0) + (b.t + b.ms/1000.0)
  def __eq__(a,b):
    return (1000 * a.t + a.ms) == (1000 * b.t + b.ms)
  def time_only(self):
    return '{:02d}:{:02d}:{:02d}.{:03d}'.format(\
              self.tm[3], self.tm[4],self.tm[5], self.ms)
  def date_only(self):
    return '{:02d}-{}-{:4d}'.format(\
              self.tm[2], self.MONTHS[self.tm[1]-1], self.tm[0] )


# Simple class to prefixes and unit names
# for Human-readable output
class Prefix:
  def __init__(self, pre, lower):
    self.pre = pre
    self.lower = lower
class Unit:
  def __init__(self, sym, prefixes, descr):
    self.sym = sym
    self.prefixes = prefixes
    self.descr = descr

GBYTES = Prefix( 'Gi', 1024*1024*1024 )
MBYTES = Prefix( 'Mi', 1024*1024 )
KBYTES = Prefix( 'Ki', 1024 )
BYTES = Unit( 'B', [ GBYTES, MBYTES, KBYTES ], 'Bytes, binary 2^N size'  )
  
GIGA = Prefix( 'G', 1E9 )
MEGA = Prefix( 'M', 1E6 )
KILO = Prefix( 'K', 1E3 )
HERTZ = Unit( 'Hz', [ GIGA, MEGA, KILO ], 'Hertz, frequency' )

def unitize(val, units):
  """Returns a human-readable string with prefix and units."""
  for u in units.prefixes:
    if val > u.lower:
      val = val // u.lower
      pre = u.pre
      break
  else:
    units = '  B'
  return str(val) + ' ' + pre + units.sym


class Disk:
  """Disk information dataclass."""
  def __init__(self, path):
    self.path = path
    self.statvfs()
    
  def statvfs(self):
    """Stat the disk drive information."""
    self.stat = uos.statvfs('/' + self.path)
    self.size = self.stat[0] * self.stat[2]
    self.free = self.stat[0] * self.stat[3]
    self.hsize = unitize(self.size, BYTES)
    self.hfree = unitize(self.free, BYTES)

  def info(self):
    """Formats the disk drive information"""
    return '{:>8s}: {:8s}(size)   {:8s}(free)'.\
        format(self.path, self.hsize, self.hfree)
    
def chunkstring(string, length):
  """Break string/bytes into fixed-length chunks, returns generator."""
  return (string[0+i:length+i] for i in range(0, len(string), length))

def serial_loopback( ser, text, vb=False ):
  """Sends and receives the message over loopbacked serial port."""
  # input is string, but we send encoded byte stream (utf-8)
  etext = text.encode('utf-8')
  nxchars = len(text)
  nxbytes = len(etext)
  print('------')
  print('  Sent string: ', text)
  print('  Sending {} letters encoded as {} bytes'.format(nxchars, nxbytes))
  # send in chunks, because hardware UART buffers are not big 
  # could be solve with threaded receive task, maybe
  ereply = bytes()
  for chunk in chunkstring(etext, 16):
    nwrite = ser.write(chunk)
    ereply += ser.read(nwrite)
  nrbytes = len(ereply)
  if nrbytes != nxbytes:
    print('  ERROR:')
    print('    Reply num. bytes:', nrbytes )
    print('    Reply bytes text:', hexdump(ereply))
    nrchars=0
    reply=''
  else:
    reply = ereply.decode('utf-8')
    nrchars = len(reply)
  match = (nxbytes == nrbytes) and (nxchars == nrchars) and (text == reply)
  print('  Received {} letters encoded as {} bytes'.format(nrchars, nrbytes))
  print('  Reply string:', reply)
  print('  Strings Match:', match )

def main():
  """Simple demo of H750 board."""

  # begin the program
  t0 = Timestamp()
  print('===========================================')
  print('Aliman STM32H750 Demo Board Example Program')
  print('started at:', t0)

  # show flash disk volumes
  disks = []
  paths = uos.listdir('/')
  for p in paths: disks.append( Disk(p) )
  for d in disks: print( d.info() )
    
  # show the CPU frequency
  freq = machine.freq()[0]
  print('cpu freq:', unitize(freq, HERTZ))

  # Micropython and Board details
  bd = uos.uname()
  print(' sysname:', bd.sysname )
  print('nodename:', bd.nodename )
  print(' release:', bd.release )
  print(' version:', bd.version )
  print(' machine:', bd.machine )

  # Blink the LED
  print('blinking: ', end='' )
  led = pyb.LED(1)
  led.on()
  for _ in range(10):
    led.toggle()
    if led.intensity() == 0: print(' __', end='')
    else:                    print(' **', end='')
    utime.sleep_ms(250)
  print()

  # Exercise the serial port, requires loopback jumper
  print('Serial Port Loopback, short RX(#1) to TX(#2) on J4')
  ser = pyb.UART(1, 115200, timeout = 500) 
  if ser:
    alpha_latin =  'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
    alpha_hangul = 'ㄱㄴㄷㄹㅁㅂㅅㅇㅈㅊㅋㅌㅍㅎㅏㅓㅗㅜㅡㅣㅐㅔㅑㅕㅛㅠ'
    message_english = 'Welcome to Aliman\'s H750 Demo Board'
    message_korean = '알리맨의 H750 대모보드에 어서오십시요'
    messages = [ alpha_latin, alpha_hangul, message_english, message_korean,]
    for msg in messages:
      serial_loopback(ser, msg)
  else:
    print('Error opening serial port')
  print('Serial Port Loopback Done.')


  print('Aliman STM32H750 Demo Board Example Program')
  t1 = Timestamp()
  print('finished at:', t1)
  dtck = t1 - t0
  print('runtime: {:.3f} secs'.format(dtck))
  print('=================================== The End')


