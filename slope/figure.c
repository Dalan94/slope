/*
 * Copyright (C) 2015  Elvis Teixeira
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
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include "slope/figure_p.h"
#include "slope/metrics_p.h"
#include "slope/item.h"
#include "slope/list.h"
#include <cairo.h>
#include <stdlib.h>

slope_figure_t* slope_figure_create()
{
    slope_figure_t *figure = malloc(sizeof(slope_figure_t));
    figure->metrics = NULL;
    figure->default_metrics = NULL;
    figure->change_callback = NULL;
    slope_color_set_name(&figure->back_color, SLOPE_WHITE);
    figure->fill_back = SLOPE_TRUE;
    return figure;
}


void slope_figure_destroy (slope_figure_t *figure)
{
    if (figure == NULL) return;
    slope_list_destroy(figure->metrics);
    free(figure);
}


void slope_figure_add_metrics (slope_figure_t *figure,
                               slope_metrics_t *metrics)
{
    if (figure == NULL) return;
    if (metrics == NULL) return;
    
    metrics->figure = figure;
    figure->metrics = slope_list_append(figure->metrics, metrics);
    figure->default_metrics = metrics;

    if (figure->change_callback) {
        (*figure->change_callback)(figure);
    }
}


slope_list_t* slope_figure_get_metrics_list (slope_figure_t *figure)
{
    if (figure == NULL) return NULL;
    return figure->metrics;
}


void slope_figure_draw (slope_figure_t *figure, cairo_t *cr,
                        const slope_rect_t *rect)
{
    cairo_stroke(cr);
    cairo_save(cr);
    /* use an easy font */
    cairo_select_font_face(cr, "Sans",
                           CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 11);
    slope_cairo_rectangle(cr, rect);
    cairo_clip(cr);
    /* fill background */
    if (figure->fill_back) {
        slope_cairo_set_color(cr, &figure->back_color);
        cairo_paint(cr);
    }
    cairo_stroke(cr);

    /* draw contents */
    slope_iterator_t *met_iter =
        slope_list_first(figure->metrics);
    while (met_iter) {
        slope_metrics_t *met = (slope_metrics_t*)
            slope_iterator_item(met_iter);
        if (slope_metrics_get_visible(met)) {
            __slope_metrics_draw(met, cr, rect);
        }
        slope_iterator_next(&met_iter);
    }
    cairo_restore(cr);
}


void slope_figure_write_to_png (slope_figure_t *figure,
                                const char *filename,
                                int width, int height)
{
    cairo_surface_t *surf = cairo_image_surface_create(
        CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr = cairo_create(surf);
    slope_rect_t rect;
    slope_rect_set(&rect, 0.0, 0.0, width, height);
    slope_figure_draw(figure, cr, &rect);
    cairo_surface_write_to_png(surf, filename);
    cairo_destroy(cr);
    cairo_surface_destroy(surf);
}


void slope_figure_set_change_callback (slope_figure_t *figure,
                                       slope_callback_t callback)
{
    if (figure == NULL) return;
    figure->change_callback = callback;
}


void slope_figure_notify_appearence_change (slope_figure_t *figure,
                                            slope_item_t *item)
{
    if (figure == NULL) return;
    (void) item; /* reserved for possible future use */
    
    if (figure->change_callback) {
        (*figure->change_callback)(figure);
    }
}


void slope_figure_notify_item_change (slope_figure_t *figure,
                                      slope_item_t *item)
{
    if (figure == NULL) return;
        
    slope_metrics_t *metrics = slope_item_get_metrics(item);
    slope_metrics_update(metrics);
    if (figure->change_callback) {
        (*figure->change_callback)(figure);
    }
}

/* slope/figure.h */
