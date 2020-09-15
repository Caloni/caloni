@echo off
git log -p -500 | grep -m 10 -A 2 "^-tags: \[ \"draft\" \]" | grep "title:" | sed "s/.*title: \"\(.*\)\"/\1/"
