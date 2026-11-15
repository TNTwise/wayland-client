// would like to make note, wayland shells are depricated.
// We use xdg desktop shell (x desktop group)
// this is standard among linux desktops, but requires extra bullshit
#include <stdio.h>
#include <string.h>


#include <syscall.h>
#include <unistd.h>
#include <sys/mman.h>

#include <wayland-client.h>
#include "xdg-shell-client-protocol.h"


// this is just some bullshit.
// dont worry about it.
// we gotta play ping pong with xdg so it knows we exist.
void sh_ping(void* data, struct xdg_wm_base* sh, uint32_t ser) {
    xdg_wm_base_pong(sh, ser);
}

struct xdg_wm_base_listener sh_list = {
    .ping = sh_ping
};

// this is the window itself.
// this allows us to set properties, like title and such.
// we could add listeners to it, like when the window is opened or closed, or when a keyboard input happens
// for what we want to do (display image), we dont need that shit
// nvm we need the listeners.
// look here: https://wayland-book.com/xdg-shell-basics.html
struct xdg_toplevel* top;



struct wl_compositor *compositor;
struct wl_shm *shm;
struct xdg_wm_base* shell;


void registry_global_handler
(
    void *data,
    struct wl_registry *registry,
    uint32_t name,
    const char *interface,
    uint32_t version
) {
    if (strcmp(interface, "wl_compositor") == 0) {
        compositor = wl_registry_bind(registry, name,
            &wl_compositor_interface, 3);
    } else if (strcmp(interface, "wl_shm") == 0) {
        shm = wl_registry_bind(registry, name,
            &wl_shm_interface, 1);
    } else if (strcmp(interface, "xdg_wm_base") == 0) {
        shell = wl_registry_bind(registry, name, &xdg_wm_base_interface, 1);
        xdg_wm_base_add_listener(shell, &sh_list, 0);
    }
}


void registry_global_remove_handler
(
    void *data,
    struct wl_registry *registry,
    uint32_t name
) {}

const struct wl_registry_listener registry_listener = {
    .global = registry_global_handler,
    .global_remove = registry_global_remove_handler
};

/*
Displays an image;
width, height are width and height of the image respectively
pix[][] is a c-type 3d array consisting of integers, that hold width,height,blue,green,red,alpha pixels
*/
int display_window_image(
    int width,
    int height,
    int stride,
    uint8_t pix[width][height][stride]
)
{
    // The core global object. This is a special singleton object. It is used for internal Wayland protocol features.
    // 0 is the display. Usually set by the WAYLAND_DISPLAY env var.
    // 0 means it will display on your current WAYLAND environment.
    struct wl_display *display = wl_display_connect(0);
    struct wl_registry *registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, NULL);

    // wait for the "initial" set of globals to appear
    wl_display_roundtrip(display);

    // This is a surface.
    // A surface is just a bunch of pixels
    // it has many requests it can do to the server, like destroy, and damage
    struct wl_surface *surface = wl_compositor_create_surface(compositor);
 
    
    // gonna need to figure out how to dynamically resize this <3
    
    int size = stride * height;  // bytes

    // open an anonymous file and write some zero bytes to it
    int fd = syscall(SYS_memfd_create, "buffer", 0);
    ftruncate(fd, size);

    // map it to the memory
    unsigned char *data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // we need to make this into a function to write pixel data.
    // <3
    // write to that memory.
    for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {

        struct pixel {
            // little-endian ARGB
            unsigned char blue;
            unsigned char green;
            unsigned char red;
            unsigned char alpha;
        } *px = (struct pixel *) (data + y * stride + x * 4);

        // yellow
        px->alpha = pix[width][height][0];
        px->red = pix[width][height][1];
        px->green = pix[width][height][2];
        px->blue = pix[width][height][3];
        }
    }

    // turn it into a shared memory pool
    // This takes in FD, which we can write to by modifying data itself.
    struct wl_shm_pool *pool = wl_shm_create_pool(shm, fd, size);

    // allocate the buffer in that pool
    // this is where we can draw pixels to the screen!
    // Changing A to X makes it a black window!
    struct wl_buffer *buffer = wl_shm_pool_create_buffer(pool,
        0, width, height, stride, WL_SHM_FORMAT_ARGB8888);
        
    // all the XDG specific stuff
    struct xdg_surface* xdgsurface = xdg_wm_base_get_xdg_surface(shell, surface);
    top = xdg_surface_get_toplevel(xdgsurface);
    xdg_toplevel_set_title(top, "Hello Worl");


    wl_surface_attach(surface, buffer, 0, 0); 
    wl_surface_commit(surface); // commit to the wayland compositr

    while (wl_display_dispatch(display) != -1) {
    /* This space deliberately left blank */
    }   
}

