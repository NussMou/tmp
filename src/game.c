#include "game.h"
#include "resource.h"

enum { PLAYER_IDLE, PLAYER_ROLL, PLAYER_DIE };
enum { DIR_LEFT, DIR_RIGHT };

struct {
    int x;
    int y;
    int ox;
    int oy;
    int frame;
    int state;
    int dir;
    int HP;
} player;

// by art
double j_idle_begin_time;
double game_begin_time;
float die_count_begin;
int gif_count = 0;

// by player
int generator_speed = 180;//生成速度，180楨刷新一波
int counter;
int queens_num;

void game_init() {
    // by art
    j_idle_begin_time = al_get_time();
    game_begin_time = al_get_time();

    // by player
    player.x = player.y = player.frame = 0;
    player.state = PLAYER_IDLE;
    player.dir = DIR_RIGHT;
    player.HP = 3;

    counter = generator_speed;
    queens_num = 1;
}

void game_destroy() {}

void queens_process(int n) {
    int x, y, num;
    for(int i=0; i<n; i++){
        num = rand() % 64;
        x = num / 8;
        y = num % 8;
        for(int col=0;col<8;col++){
            board[y][col]++;
        }
        for(int row=0;row<8;row++){
            board[row][x]++;
            for(int col=0;col<8;col++){
                if(row+col==x+y||row-col==y-x){
                    board[row][col]++;
                }
            }
        }//只要有攻擊到就+1
        board[y][x]=100;//rand之後把有皇后的點的值改為30
    }
}

void candy_process(){
    int candy=rand()%64;
    if(board[candy%8][candy/8]==0)
        board[candy%8][candy/8]=-100;
}

int game_process(ALLEGRO_EVENT event) {

    if (player.state == PLAYER_DIE) {
        if (al_get_time() - die_count_begin >= 2) {
            return MSG_GAME_OVER;
        }
        return MSG_NOPE;
    }

    // 測試血量顯示
    if (event.type == ALLEGRO_KEY_DOWN &&
        event.keyboard.keycode == ALLEGRO_KEY_W &&
        player.HP > 0) {
        --player.HP;
    }

    if(player.state == PLAYER_IDLE && board[player.x][player.y] < 0) {
        if (player.HP < 3)
            player.HP++;
        board[player.x][player.y] = 0;
        al_stop_sample_instance(get_candy_spi);
        al_play_sample_instance(get_candy_spi);
    }

    // player idle
    if (event.type == ALLEGRO_EVENT_KEY_DOWN && player.state == PLAYER_IDLE) {
        player.ox = player.x;
        player.oy = player.y;

        if (event.keyboard.keycode == key_left && player.x > 0) {
            --player.x;
        } else if (event.keyboard.keycode == key_right && player.x < 7) {
            ++player.x;
        } else if (event.keyboard.keycode == key_up && player.y > 0) {
            --player.y;
        } else if (event.keyboard.keycode == key_down && player.y < 7) {
            ++player.y;
        }

        if (player.x != player.ox || player.y != player.oy) {
            player.state = PLAYER_ROLL;
            player.frame = 0;
            if (player.x != player.ox) {
                player.dir = (player.x < player.ox) ? DIR_LEFT : DIR_RIGHT;
            }
            al_stop_sample_instance(jump_spi);
            al_play_sample_instance(jump_spi);
        }
    }

    // only update frame count when the event is from the scene timer
    // don't update for keyboard event
    if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == scene_timer) {
        player.frame++;
        if (player.state == PLAYER_ROLL && player.frame >= 21) {
            player.state = PLAYER_IDLE;
            player.frame = 0;
        }

        gif_count++;

        counter--;
        if (counter == 150) {
            //生成皇后
            //變數可以調整，要隨著時間調整也行
            queens_process(1 + queens_num / 8);
            //candy
            //if(number%5==0)
            candy_process();
        } else if (counter == 20) {
            al_stop_sample_instance(lightning_spi);
            al_play_sample_instance(lightning_spi);
        } else if (counter == 0) {
            //判斷扣血
            if (player.state == PLAYER_IDLE && board[player.x][player.y] >= 1) {
                player.HP--;
            } else if (player.state == PLAYER_ROLL) {
                if (player.frame < 21 / 2 && board[player.ox][player.oy] >= 1) {
                    player.HP--;
                } else if (player.frame >= 21 / 2 && board[player.x][player.y] >= 1) {
                    player.HP--;
                }
            }

            if (player.state != PLAYER_DIE && player.HP == 0) {
                player.state = PLAYER_DIE;
                die_count_begin = al_get_time();
                al_play_sample_instance(dead_sound_spi);
            }

            //清空皇后
            for(int i=0; i<8; i++){
                for(int j=0; j<8; j++){
                    board[i][j] = 0;
                }
            }
            queens_num++;
            counter = generator_speed; //counter重製
        }
    }

    return MSG_NOPE;
}

void heart_draw() {
    const int heart_size = 60;
    if (player.HP >= 1)
        al_draw_scaled_bitmap(heart, 0, 0, 22, 23, 50, 50, heart_size, heart_size, 0);
    if (player.HP >= 2)
        al_draw_scaled_bitmap(heart, 0,0 , 22, 23, 120, 50, heart_size, heart_size, 0);
    if (player.HP >= 3)
        al_draw_scaled_bitmap(heart, 0,0 , 22, 23, 190, 50, heart_size, heart_size, 0);
}

void score_draw() {
    if (player.HP > 0) {
        number = al_get_time() - game_begin_time;
        if(!easter_egg_mode){
            number = (al_get_time() - game_begin_time)*3;
        }
    }

    al_draw_textf(score, al_map_rgb(255,255,255), 400, 55, ALLEGRO_ALIGN_LEFT,  "Score: %3d", number);
}

void game_draw() {
    const float unit = 86;
    const float dx = 33;
    const float dy = 241;

    al_draw_bitmap(GBI, 0, 0, 0); // 這個是背景buffer

    // draw queens
    for (int i=0; i<8; ++i) {
        for (int j=0; j<8; ++j) {
            if(board[i][j] >=1 && board[i][j] < 20) {
                if (counter < 21) {
                    al_draw_bitmap(
                        algif_get_bitmap(Lightening_gif, al_get_time()),
                        dx + i*unit,
                        dy + j*unit,
                        0
                    );
                }

                else if (counter <= 150) {
                    const int upper_bound = unit / 2 - 3;
                    const int lower_bound = unit / 2 - 10;
                    float a = (sin(al_get_time() * 8) + 1) / 2;
                    float r = lower_bound + (upper_bound - lower_bound) * a;

                    //mode
                    if(easter_egg_mode){
                        /*
                        al_draw_filled_rectangle(
                            dx + (i+0.5)*unit - r,
                            dy + (j+0.5)*unit - r,
                            dx + (i+0.5)*unit + r,
                            dy + (j+0.5)*unit + r,
                            al_map_rgba(255, 0, 0, 200)
                        );*/
                        al_draw_scaled_bitmap(
                            algif_get_frame_bitmap(
                                warn_gif,
                                gif_count / 6 % warn_gif->frames_count),
                            200,
                            203,
                            94,
                            94,
                            dx + i*unit,
                            dy + j*unit,
                            unit,
                            unit,
                            0
                        );
                    }
                }
            }
            if (board[i][j] >= 90) {
                al_draw_scaled_bitmap(
                    algif_get_bitmap(Queen_gif, al_get_time()),
                    0,
                    0,
                    480,
                    480,
                    dx + i*unit,
                    dy + j*unit,
                    unit,
                    unit,
                    0
                );
            }
            //畫candy
            if (board[i][j] < 0) {
                al_draw_scaled_bitmap(
                    algif_get_frame_bitmap(
                        candy_gif, gif_count / 6 % candy_gif->frames_count),
                    175,
                    211,
                    140,
                    140,
                    dx + i*unit,
                    dy + j*unit,
                    unit,
                    unit,
                    0
                );
            }
        }
    }

    // draw player
    if (player.state == PLAYER_IDLE) {
        al_draw_bitmap(
            algif_get_bitmap(JI_gif, al_get_time()),
            dx + player.x*unit,
            dy + player.y*unit,
            player.dir == DIR_LEFT ? ALLEGRO_FLIP_HORIZONTAL : 0);
    } else if(player.state == PLAYER_ROLL){
        al_draw_bitmap(
            algif_get_bitmap(JJ_gif, player.frame/21.0*0.84),
            dx + (player.x*(player.frame/21.0)+player.ox*(1-player.frame/21.0))*unit,
            dy + (player.y*(player.frame/21.0)+player.oy*(1-player.frame/21.0))*unit,
            player.dir == DIR_LEFT ? ALLEGRO_FLIP_HORIZONTAL : 0);
    } else if(player.state == PLAYER_DIE) {
        if (al_get_time() - die_count_begin <= 0.5){
            al_draw_bitmap(
                algif_get_bitmap(JD_gif, al_get_time() - die_count_begin),
                dx + player.x*unit,
                dy + player.y*unit,
                player.dir == DIR_LEFT ? ALLEGRO_FLIP_HORIZONTAL : 0);
        } else {
            al_draw_bitmap(
                JD_stop,
                dx + player.x*unit,
                dy + player.y*unit,
                player.dir == DIR_LEFT ? ALLEGRO_FLIP_HORIZONTAL : 0);
        }
    }

    heart_draw();
    score_draw();
}