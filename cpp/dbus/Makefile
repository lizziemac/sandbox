# docker rm -f dbus-container
# docker run -d --name dbus-container dbus-service
TARGETS := server notifier rxtx
.PHONY: all clean $(TARGETS)

$(TARGETS):
	@mkdir -p build/$@
	@cmake -S $@ -B build/$@
	@cmake --build build/$@

all: $(TARGETS)

clean:
	@rm -rf build