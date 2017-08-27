/*
 * Copyright (C) 2016  Elvis Teixeira
 *
 * This source code is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <math.h>
#include <slope.h>

int main(int argc, char *argv[]) {
  SlopeFigure *figure;
  SlopeScale *scale;
  SlopeItem *series;
  double *x, *y;

  figure = slope_figure_new();

  /* create some sinusoidal data points */
  long k, n = 50;
  x = g_malloc(n * sizeof(double));
  y = g_malloc(n * sizeof(double));
  double dx = 4.0 * G_PI / n;

  for (k = 0; k < n; ++k) {
    x[k] = k * dx;
    y[k] = sin(x[k]);
  }

  scale = slope_xyscale_new();
  slope_figure_add_scale(SLOPE_FIGURE(figure), scale);

  series = slope_xyseries_new_filled("Sine", x, y, n, SLOPE_BLUE, SLOPE_GREEN,SLOPE_SERIES_CIRCLES | SLOPE_SERIES_LINE);
  slope_scale_add_item(scale, series);

  slope_figure_write_to_png(SLOPE_FIGURE(figure), "test.png", 500, 300);
  slope_figure_write_to_svg(SLOPE_FIGURE(figure), "test.svg", 500, 300);
  slope_figure_write_to_pdf(SLOPE_FIGURE(figure), "test.pdf", 500, 300);

  g_free(x);
  g_free(y);

  return 0;
}
