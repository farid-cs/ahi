APP = snake
PREFIX = /usr/local/bin

$(APP):
	go build -o $@

install: $(APP)
	cp $(APP) $(PREFIX)

uninstall:
	rm -f $(PREFIX)/$(APP)

clean:
	go clean

.PHONY: $(APP) clean install
