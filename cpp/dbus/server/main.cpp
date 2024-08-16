#include <gio/gio.h>
#include <iostream>

static void handle_method_call(GDBusConnection *connection,
                               const gchar *sender,
                               const gchar *object_path,
                               const gchar *interface_name,
                               const gchar *method_name,
                               GVariant *parameters,
                               GDBusMethodInvocation *invocation,
                               gpointer user_data) {
    if (g_strcmp0(method_name, "SayHello") == 0) {
        g_dbus_method_invocation_return_value(invocation, g_variant_new("(s)", "Hello from server!"));
    }
}

static const GDBusInterfaceVTable interface_vtable = {
    handle_method_call,
    NULL,
    NULL
};

static void on_bus_acquired(GDBusConnection *connection,
                            const gchar *name,
                            gpointer user_data) {
    GDBusNodeInfo *introspection_data;
    GError *error = NULL;

    const gchar introspection_xml[] =
        "<node>"
        "  <interface name='com.example.SimpleService'>"
        "    <method name='SayHello'>"
        "      <arg type='s' name='message' direction='in'/>"
        "      <arg type='s' name='response' direction='out'/>"
        "    </method>"
        "  </interface>"
        "</node>";

    introspection_data = g_dbus_node_info_new_for_xml(introspection_xml, &error);
    if (error) {
        g_printerr("Error: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    guint registration_id = g_dbus_connection_register_object(connection,
                                                              "/com/example/SimpleService",
                                                              introspection_data->interfaces[0],
                                                              &interface_vtable,
                                                              NULL,  /* user_data */
                                                              NULL,  /* user_data_free_func */
                                                              &error);

    if (registration_id == 0) {
        g_printerr("Error: %s\n", error->message);
        g_clear_error(&error);
    }

    g_dbus_node_info_unref(introspection_data);
}

int main() {
    GMainLoop *loop;
    loop = g_main_loop_new(NULL, FALSE);

    g_bus_own_name(G_BUS_TYPE_SESSION,
                   "com.example.SimpleService",
                   G_BUS_NAME_OWNER_FLAGS_NONE,
                   on_bus_acquired,
                   NULL,
                   NULL,
                   NULL,
                   NULL);

    std::cout << "[server] is running..." << std::endl;

    g_main_loop_run(loop);
    g_main_loop_unref(loop);

    return 0;
}
