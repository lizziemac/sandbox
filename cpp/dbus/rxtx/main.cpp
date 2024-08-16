#include <gio/gio.h>
#include <iostream>

int main() {
    GError *error = NULL;
    GDBusConnection *connection;
    GVariant *result;

    connection = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &error);
    if (error) {
        g_printerr("Error: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    std::cout << "[rxtx] is running..." << std::endl;

    GVariant *parameters = g_variant_new ("(s)", "Hello");

    result = g_dbus_connection_call_sync(connection,
                       "com.example.SimpleService",   // bus name
                       "/com/example/SimpleService",  // object path
                       "com.example.SimpleService",   // interface name
                       "SayHello",                    // method name
                       parameters,                    // parameters
                       G_VARIANT_TYPE("(s)"),         // expected reply type
                       G_DBUS_CALL_FLAGS_NONE,
                       -1,
                       NULL,
                       &error);

    if (error) {
        g_printerr("Error: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    gchar *response;
    g_variant_get(result, "(s)", &response);
    g_print("Response: %s\n", response);
    g_free(response);
    g_variant_unref(result);
    g_object_unref(connection);

    return 0;
}
