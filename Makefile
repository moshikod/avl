TARGET ?= demo

avl: compile

clean:
	rm -f ./example ./demo ./test

compile:
	g++ -std=c++11 -DNDEBUG -Wall -g -o $(TARGET) $(TARGET).cpp

run: compile
	@./$(TARGET)

docker-run:
	-@docker tag avl:$(TARGET) avl:$(TARGET)-old
	@docker build --build-arg TARGET=$(TARGET) -t avl:$(TARGET) -f avl.dockerfile .
	-@docker rmi -f avl:$(TARGET)-old
	@docker run -it --rm --name avl-$(TARGET) avl:$(TARGET)

docker-clean:
	-@docker rmi -f avl:example avl:demo avl:test
