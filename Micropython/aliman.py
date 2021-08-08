import uos
import machine
import pyb
import utime

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
  for u in units.prefixes:
    if val > u.lower:
      val = val // u.lower
      pre = u.pre
      break
  else:
    units = '  B'
  return str(val) + ' ' + pre + units.sym

class Disk:
  def __init__(self, path):
    self.path = path
    self.statvfs()
    
  def statvfs(self):
    self.stat = uos.statvfs('/' + self.path)
    self.size = self.stat[0] * self.stat[2]
    self.free = self.stat[0] * self.stat[3]
    self.hsize = unitize(self.size, BYTES)
    self.hfree = unitize(self.free, BYTES)

  def info(self):
    return '{:>8s}: {:8s}(size)   {:8s}(free)'.\
        format(self.path, self.hsize, self.hfree)
    

# show flash disk volumes
disks = []
paths = uos.listdir('/')
for p in paths: disks.append( Disk(p) )
for d in disks: print( d.info() )
  
# CPU frequency
freq = machine.freq()[0]
print('cpu freq:', unitize(freq, HERTZ))

# Micropython and Board details
bd = uos.uname()
print(' sysname:', bd.sysname )
print('nodename:', bd.nodename )
print(' release:', bd.release )
print(' version:', bd.version )
print(' machine:', bd.machine )

print('blinking: ', end='' )
led = pyb.LED(1)
led.on()
for _ in range(10):
  led.toggle()
  if led.intensity() == 0: print(' __', end='')
  else:                    print(' **', end='')
  utime.sleep_ms(250)

print()

print('Aliman STM32H750 Demo Board, The End.')


  





