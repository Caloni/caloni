@echo off
grep "guid" public\tags\index.xml | sed "s/.*tags\/\([a-z]\+\).*/\1/" | sort
