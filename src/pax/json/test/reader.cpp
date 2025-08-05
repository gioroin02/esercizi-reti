#include "../exports.hpp"

#include "../../memory/exports.hpp"

using namespace pax;

#include <stdio.h>

#define COLOR_RESET "\x1b[0m"

#define FRONT_RED    "\x1b[31m"
#define FRONT_GREEN  "\x1b[32m"
#define FRONT_YELLOW "\x1b[33m"
#define FRONT_BLUE   "\x1b[34m"
#define FRONT_PURPLE "\x1b[35m"
#define FRONT_AZURE  "\x1b[36m"

#define RED(expr)    FRONT_RED    expr COLOR_RESET
#define GREEN(expr)  FRONT_GREEN  expr COLOR_RESET
#define YELLOW(expr) FRONT_YELLOW expr COLOR_RESET
#define BLUE(expr)   FRONT_BLUE   expr COLOR_RESET
#define PURPLE(expr) FRONT_PURPLE expr COLOR_RESET
#define AZURE(expr)  FRONT_AZURE  expr COLOR_RESET

struct App_Config_Flags
{
    isiz flags = 0;
};

struct App_Config_Display
{
    usiz width      = 0;
    usiz height     = 0;
    usiz color_bits = 0;
    usiz depth_bits = 0;
};

struct App_Config_Network
{
    str8 server_addr = {};
    usiz server_port = 0;
};

struct App_Config
{
    App_Config_Flags   flags   = {};
    App_Config_Display display = {};
    App_Config_Network network = {};

    b32 paused = 0;
};

static const str8 CONFIG = pax_str8(
    "{\n"
        "\t\"flags\": [1, 4],\n"
        "\t\"display\": { \"width\": 720, \"height\": 480 },\n"
        "\t\"network\": { \"server_addr\": \"127.0.0.1\", \"server_port\": 5000 },\n"
        "\t\"paused\": true\n"
    "}\n"
);

static const str8 CONFIG_PART_0 = pax_str8(
    "{ \"flags\": [1, 4], \"display\": { \"width\": 720, \"height\": 480 }, \"network\": { \"ser"
);

static const str8 CONFIG_PART_1 = pax_str8(
    "ver_addr\": \"127.0.0.1\", \"server_port\": 50000 }, \"paused\": true }\n"
);

b32
app_config_flags_json_read(App_Config_Flags* self, JSON_Reader* reader, Arena* arena)
{
    JSON_Event event = json_reader_event(reader, arena);

    while (event.group == JSON_GROUP_ARRAY) {
        if (event.type == JSON_EVENT_STOP) break;

        if (event.type == JSON_EVENT_ABSOLUTE)
            self->flags |= event.absolute;

        event = json_reader_event(reader, arena);
    }

    return 1;
}

b32
app_config_display_json_read(App_Config_Display* self, JSON_Reader* reader, Arena* arena)
{
    JSON_Event event = json_reader_event(reader, arena);

    while (event.group == JSON_GROUP_OBJECT) {
        if (event.type == JSON_EVENT_STOP) break;

        if (event.type == JSON_EVENT_ABSOLUTE) {
            if (str8_is_equal(event.name, pax_str8("width")) != 0)
                self->width = event.absolute;

            if (str8_is_equal(event.name, pax_str8("height")) != 0)
                self->height = event.absolute;

            if (str8_is_equal(event.name, pax_str8("color_bits")) != 0)
                self->color_bits = event.absolute;

            if (str8_is_equal(event.name, pax_str8("depth_bits")) != 0)
                self->depth_bits = event.absolute;
        }

        event = json_reader_event(reader, arena);
    }

    return 1;
}

b32
app_config_network_json_read(App_Config_Network* self, JSON_Reader* reader, Arena* arena)
{
    JSON_Event event = json_reader_event(reader, arena);

    while (event.group == JSON_GROUP_OBJECT) {
        if (event.type == JSON_EVENT_STOP) break;

        if (event.type == JSON_EVENT_STRING) {
            if (str8_is_equal(event.name, pax_str8("server_addr")) != 0)
                self->server_addr = event.string;
        }

        if (event.type == JSON_EVENT_ABSOLUTE) {
            if (str8_is_equal(event.name, pax_str8("server_port")) != 0)
                self->server_port = event.absolute;
        }

        event = json_reader_event(reader, arena);
    }

    return 1;
}

b32
app_config_json_read(App_Config* self, JSON_Reader* reader, Arena* arena)
{
    JSON_Event event = json_reader_event(reader, arena);

    while (event.group == JSON_GROUP_OBJECT) {
        if (event.type == JSON_EVENT_STOP) break;

        if (event.type == JSON_EVENT_NAME) {
            if (str8_is_equal(event.name, pax_str8("flags")) != 0)
                app_config_flags_json_read(&self->flags, reader, arena);

            if (str8_is_equal(event.name, pax_str8("display")) != 0)
                app_config_display_json_read(&self->display, reader, arena);

            if (str8_is_equal(event.name, pax_str8("network")) != 0)
                app_config_network_json_read(&self->network, reader, arena);
        }

        if (event.type == JSON_EVENT_BOOLEAN) {
            if (str8_is_equal(event.name, pax_str8("paused")) != 0)
                self->paused = event.boolean;
        }

        event = json_reader_event(reader, arena);
    }

    return 1;
}

void
show_app_config_flags(App_Config_Flags* self)
{
    printf("flags = %llu\n", self->flags);
}

void
show_app_config_display(App_Config_Display* self)
{
    printf("width      = %llu\n", self->width);
    printf("height     = %llu\n", self->height);
    printf("color_bits = %llu\n", self->color_bits);
    printf("depth_bits = %llu\n", self->depth_bits);
}

void
show_app_config_network(App_Config_Network* self)
{
    str8 server_addr = self->server_addr;

    printf("server_addr = '%.*s'\n",
        pax_as(int, server_addr.length), server_addr.memory);

    printf("server_port = %llu\n", self->server_port);
}

void
show_app_config(App_Config* self)
{
    show_app_config_flags(&self->flags);
    printf("\n");

    show_app_config_display(&self->display);
    printf("\n");

    show_app_config_network(&self->network);
    printf("\n");

    printf("paused = %s\n",
        self->paused != 0 ? "true" : "false");
}

int
main(int argc, char** argv)
{
    Arena arena  = system_reserve(16);
    buf8  buffer = buf8_reserve(&arena, 4 * MEMORY_KIB);

    buf8_write_str8_tail(&buffer, CONFIG);
    buf8_normalize(&buffer);

    printf(GREEN("[start]") "\n%.*s" GREEN("[stop]") "\n",
        pax_as(int, buffer.size), buffer.memory);

    JSON_Reader reader = json_reader_make(&arena, 128, &buffer);

    printf("\n");

    App_Config config = {};

    app_config_json_read(&config, &reader, &arena);

    show_app_config(&config);
}
