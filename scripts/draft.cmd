@echo off
grep -m 20 "<title>" public\tags\draft\index.xml | sed -e "s/.*<title>\(.*\)<\/title>/\1/" -e "/draft on/d"
