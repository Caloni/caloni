@echo off
git add --all
git commit -m "publish: %*"
git pull
git push

hugo

pushd public
git add -f tags
git add --all
git commit -m "publish: %*"
git push
popd
