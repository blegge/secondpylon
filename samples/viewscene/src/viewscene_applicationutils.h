// Copyright 2009 Brian Legge

#ifndef SAMPLES_VIEWSCENE_SRC_VIEWSCENE_APPLICATIONUTILS_H_
#define SAMPLES_VIEWSCENE_SRC_VIEWSCENE_APPLICATIONUTILS_H_

typedef void (*RenderCallback)();

struct ApplicationUtils {
  static void run_app(RenderCallback render_callback);
};

#endif  // SAMPLES_VIEWSCENE_SRC_VIEWSCENE_APPLICATIONUTILS_H_
