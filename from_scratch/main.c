#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include "xdg-shell-client-protocol.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

struct wl_compositor* comp;
struct wl_surface* srfc;

// each window has its own offscreen buffer in the memory
// every time you send a frame to the server
// the surface (wl_surface srfc) has a buffer
struct wl_buffer* bfr;

struct wl_shm* shm;
struct xdg_wm_base* sh;

// this is the actual window itself.
struct xdg_toplevel* top;

uint8_t* pixl;
uint16_t w = 200;
uint16_t h = 100;

// we need to create some shared memory because of some bs
int32_t alc_shm(uint64_t sz) {
    int8_t name[8];
    name[0] = '/';
    name[7] = 0;

    for (uint8_t i = 1; i < 6; i++) {
        name[i] = (rand() & 23) + 97; // bunch of random letters

    }
    // opening shared memory with permissions
    int32_t fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, S_IWUSR | S_IRUSR | S_IWUSR);
    shm_unlink(name);
    ftruncate(fd, sz);
    return fd;
}

void draw() {

}

void resz() {
    int32_t fd = alc_shm(4 * w * h); // each pixel needs r,g,b,h
    pixl = mmap(0, w * h * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    struct wl_shm_pool* pool = wl_shm_create_pool(shm, fd, w * h * 4);
    bfr = wl_shm_pool_create_buffer(pool, 0, w, h, w*4, WL_SHM_FORMAT_ARGB8888);

    wl_shm_pool_destroy(pool);
    close(fd);
}

void xrfc_conf(void* data, struct xdg_surface* xrfc, uint32_t ser) {
    xdg_surface_ack_configure(xrfc, ser);
    if (!pixl) {
        resz();
    }
    draw();
    wl_surface_attach(srfc, bfr, 0, 0);
    wl_surface_damage(srfc, 0, 0, w, h);
    // tells the server we are done rendering, and to commit the latest stage of the window.
    wl_surface_commit(srfc);
}



struct xdg_surface_listener xrfc_list = {
    .configure = xrfc_conf
};

void top_conf(void* data, struct xdg_toplevel* top, int32_t w, int32_t h, struct wl_array* state) {

}

void top_cls(void* data, struct xdg_toplevel* top) {
    
}

struct xdg_toplevel_listener top_list = {
    .configure = top_conf,
    .close = top_cls
};

void sh_ping(void* data, struct xdg_wm_base* sh, uint32_t ser) {
    xdg_wm_base_pong(sh, ser);
}

struct xdg_wm_base_listener sh_list = {
    .ping = sh_ping
};

// This sets things that will be consistent between the server and the client
void reg_glob(void* data, struct wl_registry* reg, uint32_t name, const char* intf, uint32_t v) {
    if (!strcmp(intf, wl_compositor_interface.name)) {
        // each object in wayland has a name so you can identify them
        comp = wl_registry_bind(reg, name, &wl_compositor_interface, 4);
    }
    else if (!strcmp(intf, wl_shm_interface.name)) {
        // each object in wayland has a name so you can identify them
        shm = wl_registry_bind(reg, name, &wl_shm_interface, 1);
    }
    else if (!strcmp(intf, xdg_wm_base_interface.name)) {
        // each object in wayland has a name so you can identify them
        sh = wl_registry_bind(reg, name, &xdg_wm_base_interface, 1);
        xdg_wm_base_add_listener(sh, &sh_list, 0);
    }
}

// removes any objects that are not needed anymore
void reg_glob_remove(void *data, struct wl_registry* reg, uint32_t name) {

}

struct wl_registry_listener reg_list = {
    .global = reg_glob,
    .global_remove = reg_glob_remove
};

int8_t main() {
    // This connects to the current wayland server (0)
    struct wl_display* dlsp = wl_display_connect(0);
    if (!dlsp) {
        return -1;
    }

    
    // This is a mailbox for the wayland server to connect to
    // and send information about it
    struct wl_registry* reg = wl_display_get_registry(dlsp);

    // Sets up listener and adds it to our registry

    wl_registry_add_listener(reg, &reg_list, 0);

    // Looking for data from server
    wl_display_roundtrip(dlsp);

    srfc = wl_compositor_create_surface(comp);

    struct xdg_surface* xsrfc = xdg_wm_base_get_xdg_surface(sh, srfc);
    xdg_surface_add_listener(xsrfc, &xrfc_list, 0);
    top = xdg_surface_get_toplevel(xsrfc);
    xdg_toplevel_add_listener(top, &top_list, 0);
    xdg_toplevel_set_title(top, "Hello Worl");
    wl_surface_commit(srfc);

    while (wl_display_dispatch(dlsp));

    // Always clean up after the fact
    wl_surface_destroy(srfc);
    
    wl_display_disconnect(dlsp);

    if (bfr) {
        wl_buffer_destroy(bfr);
    }

    return 0;
}
