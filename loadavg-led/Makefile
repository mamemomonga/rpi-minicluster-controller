.PHONY: build deps clean

build: loadavg-led

loadavg-led: deps
	go build -o $@ .

deps:
	go get -v -d .

clean:
	rm -f loadavg-led

