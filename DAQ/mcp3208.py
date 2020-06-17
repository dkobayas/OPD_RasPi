#!/usr/bin/env python
# -*- coding: utf-8 -*-

import time
import spidev

class MCP3208_Class:

    def __init__(self, ref_volts):
        self.ref_volts = ref_volts
        self.spi = spidev.SpiDev()
        self.spi.open(0, 0)
        self.spi.max_speed_hz = 1000000 # 1MHz

    def GetVoltage(self, ch):
        adc = self.spi.xfer2([1, (8+ch)<<4, 0])
        #adc = self.spi.xfer2(ch)
        #data = ((adc[1]&3) << 8) + adc[2]
        data = ((adc[1]&0x0f) << 8) + adc[2]
        volts = (data * self.ref_volts) / float(1023)
        volts = round(volts, 4)
        return volts

    def Cleanup(self):
        self.spi.close()

if __name__ == '__main__':
    ADC = MCP3208_Class(ref_volts=1.65)
    ofname = input('input file name: ') ### it is for python3 only. this causes an error with python2
    t_thr = input('measurement time[s]: ') ### it is for python3 only. this causes an error with python2
    file = open("../Data/dat/"+ofname+".dat", 'w')
    t_start = time.time()
    try:
        while True:
            t_current = time.time() - t_start
            volts0 = ADC.GetVoltage(ch=0)
            volts1 = ADC.GetVoltage(ch=1)
            #print("volts: P1: {:4.3}, P2: {:4.3}".format(volts0, volts1))
            file.write("{:4.4} {:4.4} {:4.4}\n".format(t_current, volts0, volts1))
            time.sleep(1)
            if t_current > float(t_thr):
                print("finish with measurement time: {:1.5}[s]".format(t_current))
                break

    except KeyboardInterrupt:
        print("Ctr+C")
    except Exception as e:
        print(str(e))
    finally:
        ADC.Cleanup()
        file.close()
        print("exit program")
