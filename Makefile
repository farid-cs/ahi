APP = snake
PREFIX = /usr/local/bin

all: $(APP)

$(APP):
	go build -o $@

install: $(APP)
	cp $(APP) $(PREFIX)

uninstall:
	rm -f $(PREFIX)/$(APP)

clean:
	rm -f $(APP)

.PHONY: all clean install
