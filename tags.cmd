@echo off
cat public\tags\index.xml | grep "guid" | sed "s/.*tags\/\([a-z]\+\).*/\1/" | sort
