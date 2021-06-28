import os
import sys
import subprocess
import time


def excuteCommand(com):
   ex = subprocess.Popen(com,stdout=subprocess.PIPE,shell=True)
   out, err = ex.communicate()
   status = ex.wait()
   print("cmd in:", com)
   print("cmd out: ", out)

lang = sys.argv[1]

files = os.listdir('.')

tif_list = [_ for _ in files if _[-4:] == '.tif']
box_list = [_ for _ in files if _[-4:] == '.box']

# step 1  make box
#for tif in tif_list:
#    name = os.path.splitext(tif)
#    os.system('tesseract %s %s -l %s batch.nochop makebox' % (tif, name, lang))

# step 2  make tr
for tif in tif_list:
    name = os.path.splitext(tif)[0]
    excuteCommand('tesseract %s %s nobatch box.train' % (tif, name))

# step 3  unicharset
excuteCommand('unicharset_extractor %s' % ' '.join(box_list))

# step 4  shapetable
tr_list = [_ for _ in os.listdir('.') if _[-3:] == '.tr']
excuteCommand('shapeclustering -F %s.font_properties -U unicharset %s' % (lang, ' '.join(tr_list)))

# step 5  mftraining
excuteCommand('mftraining -F %s.font_properties -U unicharset -O unicharset %s' % (lang, ' '.join(tr_list)))

# step 6
excuteCommand('cntraining %s' % ' '.join(tr_list))

# step 7 rename
os.rename('shapetable', '%s.shapetable' % lang)
os.rename('normproto', '%s.normproto' % lang)
os.rename('inttemp', '%s.inttemp' % lang)
os.rename('pffmtable', '%s.pffmtable' % lang)
os.rename('unicharset', '%s.unicharset' % lang)

# step 8 combine_tessdata
excuteCommand('combine_tessdata %s.' % lang)

# remove
os.remove('%s.shapetable' % lang)
os.remove('%s.normproto' % lang)
os.remove('%s.inttemp' % lang)
os.remove('%s.pffmtable' % lang)
os.remove('%s.unicharset' % lang)
for tr in tr_list:
    os.remove(tr)

