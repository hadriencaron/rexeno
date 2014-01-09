/**************************************************************************
 *
 * Copyright 2009 VMware, Inc.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL VMWARE AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#include "image.h"

#include "vg_translate.h"
#include "vg_context.h"
#include "matrix.h"
#include "renderer.h"
#include "util_array.h"
#include "api_consts.h"
#include "shaders_cache.h"
#include "shader.h"

#include "pipe/p_context.h"
#include "pipe/p_screen.h"
#include "pipe/p_inlines.h"
#include "util/u_blit.h"
#include "util/u_tile.h"
#include "util/u_memory.h"
#include "util/u_math.h"

static enum pipe_format vg_format_to_pipe(VGImageFormat format)
{
   switch(format) {
   case VG_sRGB_565:
      return PIPE_FORMAT_R5G6B5_UNORM;
   case VG_sRGBA_5551:
      return PIPE_FORMAT_A1R5G5B5_UNORM;
   case VG_sRGBA_4444:
      return PIPE_FORMAT_A4R4G4B4_UNORM;
   case VG_sL_8:
   case VG_lL_8:
      return PIPE_FORMAT_L8_UNORM;
   case VG_BW_1:
      return PIPE_FORMAT_A8R8G8B8_UNORM;
   case VG_A_8:
      return PIPE_FORMAT_A8_UNORM;
#ifdef OPENVG_VERSION_1_1
   case VG_A_1:
   case VG_A_4:
      return PIPE_FORMAT_A8_UNORM;
#endif
   default:
      return PIPE_FORMAT_A8R8G8B8_UNORM;
   }
}

static INLINE void vg_sync_size(VGfloat *src_loc, VGfloat *dst_loc)
{
   src_loc[2] = MIN2(src_loc[2], dst_loc[2]);
   src_loc[3] = MIN2(src_loc[3], dst_loc[3]);
   dst_loc[2] = src_loc[2];
   dst_loc[3] = src_loc[3];
}


static void vg_copy_texture(struct vg_context *ctx,
                            struct pipe_texture *dst, VGint dx, VGint dy,
                            struct pipe_texture *src, VGint sx, VGint sy,
                            VGint width, VGint height)
{
   VGfloat dst_loc[4], src_loc[4];
   VGfloat dst_bounds[4], src_bounds[4];
   VGfloat src_shift[4], dst_shift[4], shift[4];

   dst_loc[0] = dx;
   dst_loc[1] = dy;
   dst_loc[2] = width;
   dst_loc[3] = height;
   dst_bounds[0] = 0.f;
   dst_bounds[1] = 0.f;
   dst_bounds[2] = dst->width[0];
   dst_bounds[3] = dst->height[0];

   src_loc[0] = sx;
   src_loc[1] = sy;
   src_loc[2] = width;
   src_loc[3] = height;
   src_bounds[0] = 0.f;
   src_bounds[1] = 0.f;
   src_bounds[2] = src->width[0];
   src_bounds[3] = src->height[0];

   vg_bound_rect(src_loc, src_bounds, src_shift);
   vg_bound_rect(dst_loc, dst_bounds, dst_shift);
   shift[0] = src_shift[0] - dst_shift[0];
   shift[1] = src_shift[1] - dst_shift[1];

   if (shift[0] < 0)
      vg_shift_rectx(src_loc, src_bounds, -shift[0]);
   else
      vg_shift_rectx(dst_loc, dst_bounds, shift[0]);

   if (shift[1] < 0)
      vg_shift_recty(src_loc, src_bounds, -shift[1]);
   else
      vg_shift_recty(dst_loc, dst_bounds, shift[1]);

   vg_sync_size(src_loc, dst_loc);

   if (src_loc[2] >= 0 && src_loc[3] >= 0 &&
       dst_loc[2] >= 0 && dst_loc[3] >= 0) {
      renderer_copy_texture(ctx->renderer,
                            src,
                            src_loc[0],
                            src_loc[1] + src_loc[3],
                            src_loc[0] + src_loc[2],
                            src_loc[1],
                            dst,
                            dst_loc[0],
                            dst_loc[1] + dst_loc[3],
                            dst_loc[0] + dst_loc[2],
                            dst_loc[1]);
   }

}

void vg_copy_surface(struct vg_context *ctx,
                     struct pipe_surface *dst, VGint dx, VGint dy,
                     struct pipe_surface *src, VGint sx, VGint sy,
                     VGint width, VGint height)
{
   VGfloat dst_loc[4], src_loc[4];
   VGfloat dst_bounds[4], src_bounds[4];
   VGfloat src_shift[4], dst_shift[4], shift[4];

   dst_loc[0] = dx;
   dst_loc[1] = dy;
   dst_loc[2] = width;
   dst_loc[3] = height;
   dst_bounds[0] = 0.f;
   dst_bounds[1] = 0.f;
   dst_bounds[2] = dst->width;
   dst_bounds[3] = dst->height;

   src_loc[0] = sx;
   src_loc[1] = sy;
   src_loc[2] = width;
   src_loc[3] = height;
   src_bounds[0] = 0.f;
   src_bounds[1] = 0.f;
   src_bounds[2] = src->width;
   src_bounds[3] = src->height;

   vg_bound_rect(src_loc, src_bounds, src_shift);
   vg_bound_rect(dst_loc, dst_bounds, dst_shift);
   shift[0] = src_shift[0] - dst_shift[0];
   shift[1] = src_shift[1] - dst_shift[1];

   if (shift[0] < 0)
      vg_shift_rectx(src_loc, src_bounds, -shift[0]);
   else
      vg_shift_rectx(dst_loc, dst_bounds, shift[0]);

   if (shift[1] < 0)
      vg_shift_recty(src_loc, src_bounds, -shift[1]);
   else
      vg_shift_recty(dst_loc, dst_bounds, shift[1]);

   vg_sync_size(src_loc, dst_loc);

   if (src_loc[2] > 0 && src_loc[3] > 0 &&
       dst_loc[2] > 0 && dst_loc[3] > 0) {
      if (src == dst)
         renderer_copy_surface(ctx->renderer,
                               src,
                               src_loc[0],
                               src->height - (src_loc[1] + src_loc[3]),
                               src_loc[0] + src_loc[2],
                               src->height - src_loc[1],
                               dst,
                               dst_loc[0],
                               dst->height - (dst_loc[1] + dst_loc[3]),
                               dst_loc[0] + dst_loc[2],
                               dst->height - dst_loc[1],
                               0, 0);
      else
         renderer_copy_surface(ctx->renderer,
                               src,
                               src_loc[0],
                               src->height - src_loc[1],
                               src_loc[0] + src_loc[2],
                               src->height - (src_loc[1] + src_loc[3]),
                               dst,
                               dst_loc[0],
                               dst->height - (dst_loc[1] + dst_loc[3]),
                               dst_loc[0] + dst_loc[2],
                               dst->height - dst_loc[1],
                               0, 0);
   }

}

static struct pipe_texture *image_texture(struct vg_image *img)
{
   struct pipe_texture *tex = img->texture;
   return tex;
}


static void image_cleari(struct vg_image *img, VGint clear_colori,
                         VGint x, VGint y, VGint width, VGint height)
{
   VGint *clearbuf;
   VGint i;
   VGfloat dwidth, dheight;

   clearbuf = malloc(sizeof(VGint)*width*height);
   for (i = 0; i < width*height; ++i)
      clearbuf[i] = clear_colori;

   dwidth = MIN2(width, img->width);
   dheight = MIN2(height, img->height);

   image_sub_data(img, clearbuf, width * sizeof(VGint),
                  VG_sRGBA_8888,
                  x, y, dwidth, dheight);
   free(clearbuf);
}

struct vg_image * image_create(VGImageFormat format,
                               VGint width, VGint height)
{
   struct vg_context *ctx = vg_current_context();
   struct vg_image *image = CALLOC_STRUCT(vg_image);
   enum pipe_format pformat = vg_format_to_pipe(format);
   struct pipe_texture pt, *newtex;
   struct pipe_screen *screen = ctx->pipe->screen;

   vg_init_object(&image->base, ctx, VG_OBJECT_IMAGE);

   image->format = format;
   image->width = width;
   image->height = height;

   image->sampler.wrap_s = PIPE_TEX_WRAP_CLAMP_TO_EDGE;
   image->sampler.wrap_t = PIPE_TEX_WRAP_CLAMP_TO_EDGE;
   image->sampler.wrap_r = PIPE_TEX_WRAP_CLAMP_TO_EDGE;
   image->sampler.min_img_filter = PIPE_TEX_MIPFILTER_NEAREST;
   image->sampler.mag_img_filter = PIPE_TEX_MIPFILTER_NEAREST;
   image->sampler.normalized_coords = 1;

   assert(screen->is_format_supported(screen, pformat, PIPE_TEXTURE_2D,
                                      PIPE_TEXTURE_USAGE_SAMPLER, 0));

   memset(&pt, 0, sizeof(pt));
   pt.target = PIPE_TEXTURE_2D;
   pt.format = pformat;
   pf_get_block(pformat, &pt.block);
   pt.last_level = 0;
   pt.width[0] = width;
   pt.height[0] = height;
   pt.depth[0] = 1;
   pt.tex_usage = PIPE_TEXTURE_USAGE_SAMPLER;

   newtex = screen->texture_create(screen, &pt);

   debug_assert(newtex);

   image->texture = newtex;

   vg_context_add_object(ctx, VG_OBJECT_IMAGE, image);

   image_cleari(image, 0, 0, 0, image->width, image->height);
   return image;
}

void image_destroy(struct vg_image *img)
{
   struct vg_context *ctx = vg_current_context();
   vg_context_remove_object(ctx, VG_OBJECT_IMAGE, img);


   if (img->parent) {
      /* remove img from the parent child array */
      int idx;
      struct vg_image **array =
         (struct vg_image **)img->parent->children_array->data;

      for (idx = 0; idx < img->parent->children_array->num_elements; ++idx) {
         struct vg_image *child = array[idx];
         if (child == img) {
            break;
         }
      }
      debug_assert(idx < img->parent->children_array->num_elements);
      array_remove_element(img->parent->children_array, idx);
   }

   if (img->children_array && img->children_array->num_elements) {
      /* reparent the children */
      VGint i;
      struct vg_image *parent = img->parent;
      struct vg_image **children =
         (struct vg_image **)img->children_array->data;
      if (!parent) {
         VGint min_x = children[0]->x;
         parent = children[0];

         for (i = 1; i < img->children_array->num_elements; ++i) {
            struct vg_image *child = children[i];
            if (child->x < min_x) {
               parent = child;
            }
         }
      }

      for (i = 0; i < img->children_array->num_elements; ++i) {
         struct vg_image *child = children[i];
         if (child != parent) {
            child->parent = parent;
            if (!parent->children_array) {
               parent->children_array = array_create(
                  sizeof(struct vg_image*));
            }
            array_append_data(parent->children_array,
                              &child, 1);
         } else
            child->parent = NULL;
      }
      array_destroy(img->children_array);
   }

   pipe_texture_reference(&img->texture, NULL);
   free(img);
}

void image_clear(struct vg_image *img,
                 VGint x, VGint y, VGint width, VGint height)
{
   struct vg_context *ctx = vg_current_context();
   VGfloat *clear_colorf = ctx->state.vg.clear_color;
   VGubyte r, g, b ,a;
   VGint clear_colori;
   /* FIXME: this is very nasty */
   r = float_to_ubyte(clear_colorf[0]);
   g = float_to_ubyte(clear_colorf[1]);
   b = float_to_ubyte(clear_colorf[2]);
   a = float_to_ubyte(clear_colorf[3]);
   clear_colori = r << 24 | g << 16 | b << 8 | a;
   image_cleari(img, clear_colori, x, y, width, height);
}

void image_sub_data(struct vg_image *image,
                    const void * data,
                    VGint dataStride,
                    VGImageFormat dataFormat,
                    VGint x, VGint y,
                    VGint width, VGint height)
{
   const VGint yStep = 1;
   VGubyte *src = (VGubyte *)data;
   VGfloat temp[VEGA_MAX_IMAGE_WIDTH][4];
   VGfloat *df = (VGfloat*)temp;
   VGint i;
   struct vg_context *ctx = vg_current_context();
   struct pipe_screen *screen = ctx->pipe->screen;
   struct pipe_texture *texture = image_texture(image);
   VGint xoffset = 0, yoffset = 0;

   if (x < 0) {
      xoffset -= x;
      width += x;
      x = 0;
   }
   if (y < 0) {
      yoffset -= y;
      height += y;
      y = 0;
   }

   if (width <= 0 || height <= 0) {
      vg_set_error(ctx, VG_ILLEGAL_ARGUMENT_ERROR);
      return;
   }

   if (x > image->width || y > image->width) {
      vg_set_error(ctx, VG_ILLEGAL_ARGUMENT_ERROR);
      return;
   }

   if (x + width > image->width) {
      width = image->width - x;
   }

   if (y + height > image->height) {
      height = image->height - y;
   }

   { /* upload color_data */
      struct pipe_transfer *transfer = screen->get_tex_transfer(
         screen, texture, 0, 0, 0,
         PIPE_TRANSFER_WRITE, 0, 0, texture->width[0], texture->height[0]);
      src += (dataStride * yoffset);
      for (i = 0; i < height; i++) {
         _vega_unpack_float_span_rgba(ctx, width, xoffset, src, dataFormat, temp);
         pipe_put_tile_rgba(transfer, x+image->x, y+image->y, width, 1, df);
         y += yStep;
         src += dataStride;
      }
      screen->tex_transfer_destroy(transfer);
   }
}

void image_get_sub_data(struct vg_image * image,
                        void * data,
                        VGint dataStride,
                        VGImageFormat dataFormat,
                        VGint sx, VGint sy,
                        VGint width, VGint height)
{
   struct vg_context *ctx = vg_current_context();
   struct pipe_context *pipe = ctx->pipe;
   struct pipe_screen *screen = pipe->screen;
   VGfloat temp[VEGA_MAX_IMAGE_WIDTH][4];
   VGfloat *df = (VGfloat*)temp;
   VGint y = 0, yStep = 1;
   VGint i;
   VGubyte *dst = (VGubyte *)data;

   {
      struct pipe_transfer *transfer =
         screen->get_tex_transfer(screen,
                                  image->texture,  0, 0, 0,
                                  PIPE_TRANSFER_READ,
                                  0, 0,
                                  image->x + image->width,
                                  image->y + image->height);
      /* Do a row at a time to flip image data vertically */
      for (i = 0; i < height; i++) {
#if 0
         debug_printf("%d-%d  == %d\n", sy, height, y);
#endif
         pipe_get_tile_rgba(transfer, sx+image->x, y, width, 1, df);
         y += yStep;
         _vega_pack_rgba_span_float(ctx, width, temp, dataFormat, dst);
         dst += dataStride;
      }

      screen->tex_transfer_destroy(transfer);
   }
}

struct vg_image * image_child_image(struct vg_image *parent,
                                    VGint x, VGint y,
                                    VGint width, VGint height)
{
   struct vg_context *ctx = vg_current_context();
   struct vg_image *image = CALLOC_STRUCT(vg_image);

   vg_init_object(&image->base, ctx, VG_OBJECT_IMAGE);

   image->x = parent->x + x;
   image->y = parent->y + y;
   image->width = width;
   image->height = height;
   image->parent = parent;
   image->texture = 0;
   pipe_texture_reference(&image->texture,
                          parent->texture);

   image->sampler.wrap_s = PIPE_TEX_WRAP_CLAMP_TO_EDGE;
   image->sampler.wrap_t = PIPE_TEX_WRAP_CLAMP_TO_EDGE;
   image->sampler.wrap_r = PIPE_TEX_WRAP_CLAMP_TO_EDGE;
   image->sampler.min_img_filter = PIPE_TEX_MIPFILTER_NEAREST;
   image->sampler.mag_img_filter = PIPE_TEX_MIPFILTER_NEAREST;
   image->sampler.normalized_coords = 1;

   if (!parent->children_array)
      parent->children_array = array_create(
         sizeof(struct vg_image*));

   array_append_data(parent->children_array,
                     &image, 1);

   vg_context_add_object(ctx, VG_OBJECT_IMAGE, image);

   return image;
}

void image_copy(struct vg_image *dst, VGint dx, VGint dy,
                struct vg_image *src, VGint sx, VGint sy,
                VGint width, VGint height,
                VGboolean dither)
{
   struct vg_context *ctx = vg_current_context();

   if (width <= 0 || height <= 0) {
      vg_set_error(ctx, VG_ILLEGAL_ARGUMENT_ERROR);
      return;
   }
   /* make sure rendering has completed */
   ctx->pipe->flush(ctx->pipe, PIPE_FLUSH_RENDER_CACHE, NULL);
   vg_copy_texture(ctx, dst->texture, dst->x + dx, dst->y + dy,
                   src->texture, src->x + sx, src->y + sy, width, height);
}

void image_draw(struct vg_image *img)
{
   struct vg_context *ctx = vg_current_context();
   VGfloat x1, y1;
   VGfloat x2, y2;
   VGfloat x3, y3;
   VGfloat x4, y4;
   struct matrix *matrix;

   x1 = 0;
   y1 = 0;
   x2 = img->width;
   y2 = 0;
   x3 = img->width;
   y3 = img->height;
   x4 = 0;
   y4 = img->height;

   matrix = &ctx->state.vg.image_user_to_surface_matrix;

   matrix_map_point(matrix, x1, y1, &x1, &y1);
   matrix_map_point(matrix, x2, y2, &x2, &y2);
   matrix_map_point(matrix, x3, y3, &x3, &y3);
   matrix_map_point(matrix, x4, y4, &x4, &y4);

   shader_set_drawing_image(ctx->shader, VG_TRUE);
   shader_set_paint(ctx->shader, ctx->state.vg.fill_paint);
   shader_set_image(ctx->shader, img);
   shader_bind(ctx->shader);

   renderer_texture_quad(ctx->renderer, image_texture(img),
                         img->x, img->y, img->x + img->width, img->y + img->height,
                         x1, y1, x2, y2, x3, y3, x4, y4);
}

void image_set_pixels(VGint dx, VGint dy,
                      struct vg_image *src, VGint sx, VGint sy,
                      VGint width, VGint height)
{
   struct vg_context *ctx = vg_current_context();
   struct pipe_context *pipe = ctx->pipe;
   struct pipe_screen *screen = pipe->screen;
   struct pipe_surface *surf;
   struct st_renderbuffer *strb = ctx->draw_buffer->strb;

   /* make sure rendering has completed */
   pipe->flush(pipe, PIPE_FLUSH_RENDER_CACHE, NULL);

   surf = screen->get_tex_surface(screen, image_texture(src),  0, 0, 0,
                                  PIPE_BUFFER_USAGE_GPU_READ);

   vg_copy_surface(ctx, strb->surface, dx, dy,
                   surf, sx+src->x, sy+src->y, width, height);

   screen->tex_surface_destroy(surf);
}

void image_get_pixels(struct vg_image *dst, VGint dx, VGint dy,
                      VGint sx, VGint sy,
                      VGint width, VGint height)
{
   struct vg_context *ctx = vg_current_context();
   struct pipe_context *pipe = ctx->pipe;
   struct pipe_screen *screen = pipe->screen;
   struct pipe_surface *surf;
   struct st_renderbuffer *strb = ctx->draw_buffer->strb;

   /* flip the y coordinates */
   /*dy = dst->height - dy - height;*/

   /* make sure rendering has completed */
   pipe->flush(pipe, PIPE_FLUSH_RENDER_CACHE, NULL);

   surf = screen->get_tex_surface(screen, image_texture(dst),  0, 0, 0,
                                  PIPE_BUFFER_USAGE_GPU_WRITE |
                                  PIPE_BUFFER_USAGE_GPU_READ);
   vg_copy_surface(ctx, surf, dst->x + dx, dst->y + dy,
                   strb->surface, sx, sy, width, height);

   pipe_surface_reference(&surf, NULL);
}


VGboolean vg_image_overlaps(struct vg_image *dst,
                            struct vg_image *src)
{
   if (dst == src || dst->parent == src ||
       dst == src->parent)
      return VG_TRUE;
   if (dst->parent && dst->parent == src->parent) {
      VGfloat left1 = dst->x;
      VGfloat left2 = src->x;
      VGfloat right1 = dst->x + dst->width;
      VGfloat right2 = src->x + src->width;
      VGfloat bottom1 = dst->y;
      VGfloat bottom2 = src->y;
      VGfloat top1 = dst->y + dst->height;
      VGfloat top2 = src->y + src->height;

      return !(left2 > right1 || right2 < left1 ||
               top2 > bottom1 || bottom2 < top1);
   }
   return VG_FALSE;
}

VGint image_bind_samplers(struct vg_image *img, struct pipe_sampler_state **samplers,
                          struct pipe_texture **textures)
{
   img->sampler.min_img_filter = image_sampler_filter(img->base.ctx);
   img->sampler.mag_img_filter = image_sampler_filter(img->base.ctx);
   samplers[3] = &img->sampler;
   textures[3] = img->texture;
   return 1;
}

VGint image_sampler_filter(struct vg_context *ctx)
{
    switch(ctx->state.vg.image_quality) {
    case VG_IMAGE_QUALITY_NONANTIALIASED:
       return PIPE_TEX_FILTER_NEAREST;
       break;
    case VG_IMAGE_QUALITY_FASTER:
       return PIPE_TEX_FILTER_NEAREST;
       break;
    case VG_IMAGE_QUALITY_BETTER:
       /*return PIPE_TEX_FILTER_ANISO;*/
       return PIPE_TEX_FILTER_LINEAR;
       break;
    default:
       debug_printf("Unknown image quality");
    }
    return PIPE_TEX_FILTER_NEAREST;
}