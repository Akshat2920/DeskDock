SET(SOURCES components/ui_comp_label1.c
    components/ui_comp.c
    screens/ui_Screen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_wifidisabled1_png.c
    images/ui_img_youtube_png.c
    images/ui_img_discord_png.c
    images/ui_img_spotify_png.c
    images/ui_img_terminal_png.c
    images/ui_img_folder_png.c
    images/ui_img_cogwheel_png.c
    images/ui_img_netflix_png.c
    images/ui_img_custom_png.c
    images/ui_img_refresh_png.c
    fonts/ui_font_Font2l30.c
    fonts/ui_font_Font2l50.c
    fonts/ui_font_Font2l60.c)

add_library(ui ${SOURCES})
