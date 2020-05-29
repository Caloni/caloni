@echo off
if "%1"=="" goto usage
hugo new post/%1.md
python movies.py search %1 data\post\%1.toml
gvim content\post\%1.md data\post\%1.toml
goto :eof

:usage
echo How to use: new [slug] [imdb]
