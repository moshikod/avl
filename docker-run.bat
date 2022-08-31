@echo off

set TARGET=%~1
if "%TARGET%"=="" set TARGET=demo

docker tag avl:%TARGET% avl:%TARGET%-old
docker build --build-arg TARGET=%TARGET% -t avl:%TARGET% -f avl.dockerfile .
docker rmi -f avl:%TARGET%-old
docker run -it --rm --name avl-%TARGET% avl:%TARGET%
