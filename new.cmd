@echo off
if "%1"=="" goto usage
hugo new post/%1.md
gvim content\post\%1.md
goto :eof

:usage
echo How to use: new [slug]
