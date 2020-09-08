@echo off
git log -p | grep -m 10 -A 2 "^-tags: \[ \"draft\" \]"
