#include "libtouch.h"
#include <stdio.h>


void libtouch_add_tap(libtouch_gesture *gesture, uint32_t n_fingers, uint32_t maxhold) {
  libtouch_action *touch = libtouch_gesture_add_touch(gesture,LIBTOUCH_TOUCH_DOWN);
  libtouch_action_set_threshold(touch, n_fingers);
  
  libtouch_action *release = libtouch_gesture_add_touch(gesture, LIBTOUCH_TOUCH_UP);
  libtouch_action_set_threshold(release, n_fingers);
  libtouch_action_set_duration(release, maxhold);

  libtouch_action_move_tolerance(touch, 10);
  libtouch_action_move_tolerance(release, 10);
}

libtouch_gesture *libtouch_add_leftedge_swipe(libtouch_engine *engine, uint32_t n_fingers, uint32_t margin, uint32_t height) {
  struct libtouch_target *left_edge = libtouch_target_create(engine, 0, 0, margin, height);

  libtouch_gesture *g = libtouch_gesture_create(engine);
  libtouch_action *touch = libtouch_gesture_add_touch(g,LIBTOUCH_TOUCH_DOWN);
  libtouch_action_set_target(touch, left_edge);
  libtouch_action_set_threshold(touch, n_fingers);
  
  libtouch_action *move = libtouch_gesture_add_move(g, LIBTOUCH_MOVE_POSITIVE_X);
  libtouch_action_set_threshold(move, 50);
}

int main(int argc, char *argv[]) {
  libtouch_engine *engine = libtouch_engine_create();
  libtouch_gesture *gesture = libtouch_add_leftedge_swipe(engine, 3, 50, 1080);
  libtouch_progress_tracker *tracker = libtouch_progress_tracker_create(engine);
  libtouch_progress_register_touch(tracker, 0, 0, LIBTOUCH_TOUCH_DOWN, 20, 100);
  libtouch_progress_register_touch(tracker, 0, 1, LIBTOUCH_TOUCH_DOWN, 20, 200);
  libtouch_progress_register_touch(tracker, 0, 2, LIBTOUCH_TOUCH_DOWN, 20, 300);
  libtouch_progress_register_move(tracker, 40, 0, 100, 100);
  libtouch_progress_register_move(tracker, 40, 1, 100, 200);
  libtouch_progress_register_move(tracker, 40, 2, 100, 300);
  if(libtouch_handle_finished_gesture(tracker) != NULL){
    printf("YES!");
  }
  
  
}