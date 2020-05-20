@echo off
pushd content\post
git add --all
git commit -m "publish: %*"
git pull
git push
popd

hugo

pushd public
git add --all
git commit -m "publish: %*"
git push
popd

cp public/index.xml calonibot
pushd calonibot
git add --all
git commit -m "publish: %*"
git pull
git push
popd

git add --all
git commit -m "publish: %*"
git push
