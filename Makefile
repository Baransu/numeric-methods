run:
	@make build task=$(task)
	@./output/main_$(task)

build: 
	@g++ -lm main_$(task).cpp -o output/main_$(task) -Wno-c++11-extensions
