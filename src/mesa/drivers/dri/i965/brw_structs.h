/*
 Copyright (C) Intel Corp.  2006.  All Rights Reserved.
 Intel funded Tungsten Graphics to
 develop this 3D driver.

 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:

 The above copyright notice and this permission notice (including the
 next paragraph) shall be included in all copies or substantial
 portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 **********************************************************************/
 /*
  * Authors:
  *   Keith Whitwell <keithw@vmware.com>
  */


#ifndef BRW_STRUCTS_H
#define BRW_STRUCTS_H

struct brw_urb_fence
{
   struct
   {
      unsigned length:8;
      unsigned vs_realloc:1;
      unsigned gs_realloc:1;
      unsigned clp_realloc:1;
      unsigned sf_realloc:1;
      unsigned vfe_realloc:1;
      unsigned cs_realloc:1;
      unsigned pad:2;
      unsigned opcode:16;
   } header;

   struct
   {
      unsigned vs_fence:10;
      unsigned gs_fence:10;
      unsigned clp_fence:10;
      unsigned pad:2;
   } bits0;

   struct
   {
      unsigned sf_fence:10;
      unsigned vf_fence:10;
      unsigned cs_fence:11;
      unsigned pad:1;
   } bits1;
};

/* State structs for the various fixed function units:
 */


struct thread0
{
   unsigned pad0:1;
   unsigned grf_reg_count:3;
   unsigned pad1:2;
   unsigned kernel_start_pointer:26; /* Offset from GENERAL_STATE_BASE */
};

struct thread1
{
   unsigned ext_halt_exception_enable:1;
   unsigned sw_exception_enable:1;
   unsigned mask_stack_exception_enable:1;
   unsigned timeout_exception_enable:1;
   unsigned illegal_op_exception_enable:1;
   unsigned pad0:3;
   unsigned depth_coef_urb_read_offset:6;	/* WM only */
   unsigned pad1:2;
   unsigned floating_point_mode:1;
   unsigned thread_priority:1;
   unsigned binding_table_entry_count:8;
   unsigned pad3:5;
   unsigned single_program_flow:1;
};

struct thread2
{
   unsigned per_thread_scratch_space:4;
   unsigned pad0:6;
   unsigned scratch_space_base_pointer:22;
};


struct thread3
{
   unsigned dispatch_grf_start_reg:4;
   unsigned urb_entry_read_offset:6;
   unsigned pad0:1;
   unsigned urb_entry_read_length:6;
   unsigned pad1:1;
   unsigned const_urb_entry_read_offset:6;
   unsigned pad2:1;
   unsigned const_urb_entry_read_length:6;
   unsigned pad3:1;
};



struct brw_clip_unit_state
{
   struct thread0 thread0;
   struct
   {
      unsigned pad0:7;
      unsigned sw_exception_enable:1;
      unsigned pad1:3;
      unsigned mask_stack_exception_enable:1;
      unsigned pad2:1;
      unsigned illegal_op_exception_enable:1;
      unsigned pad3:2;
      unsigned floating_point_mode:1;
      unsigned thread_priority:1;
      unsigned binding_table_entry_count:8;
      unsigned pad4:5;
      unsigned single_program_flow:1;
   } thread1;

   struct thread2 thread2;
   struct thread3 thread3;

   struct
   {
      unsigned pad0:9;
      unsigned gs_output_stats:1; /* not always */
      unsigned stats_enable:1;
      unsigned nr_urb_entries:7;
      unsigned pad1:1;
      unsigned urb_entry_allocation_size:5;
      unsigned pad2:1;
      unsigned max_threads:5; 	/* may be less */
      unsigned pad3:2;
   } thread4;

   struct
   {
      unsigned pad0:13;
      unsigned clip_mode:3;
      unsigned userclip_enable_flags:8;
      unsigned userclip_must_clip:1;
      unsigned negative_w_clip_test:1;
      unsigned guard_band_enable:1;
      unsigned viewport_z_clip_enable:1;
      unsigned viewport_xy_clip_enable:1;
      unsigned vertex_position_space:1;
      unsigned api_mode:1;
      unsigned pad2:1;
   } clip5;

   struct
   {
      unsigned pad0:5;
      unsigned clipper_viewport_state_ptr:27;
   } clip6;


   float viewport_xmin;
   float viewport_xmax;
   float viewport_ymin;
   float viewport_ymax;
};

struct brw_wm_unit_state
{
   struct thread0 thread0;
   struct thread1 thread1;
   struct thread2 thread2;
   struct thread3 thread3;

   struct {
      unsigned stats_enable:1;
      unsigned depth_buffer_clear:1;
      unsigned sampler_count:3;
      unsigned sampler_state_pointer:27;
   } wm4;

   struct
   {
      unsigned enable_8_pix:1;
      unsigned enable_16_pix:1;
      unsigned enable_32_pix:1;
      unsigned enable_con_32_pix:1;
      unsigned enable_con_64_pix:1;
      unsigned pad0:1;

      /* These next four bits are for Ironlake+ */
      unsigned fast_span_coverage_enable:1;
      unsigned depth_buffer_clear:1;
      unsigned depth_buffer_resolve_enable:1;
      unsigned hierarchical_depth_buffer_resolve_enable:1;

      unsigned legacy_global_depth_bias:1;
      unsigned line_stipple:1;
      unsigned depth_offset:1;
      unsigned polygon_stipple:1;
      unsigned line_aa_region_width:2;
      unsigned line_endcap_aa_region_width:2;
      unsigned early_depth_test:1;
      unsigned thread_dispatch_enable:1;
      unsigned program_uses_depth:1;
      unsigned program_computes_depth:1;
      unsigned program_uses_killpixel:1;
      unsigned legacy_line_rast: 1;
      unsigned transposed_urb_read_enable:1;
      unsigned max_threads:7;
   } wm5;

   float global_depth_offset_constant;
   float global_depth_offset_scale;

   /* for Ironlake only */
   struct {
      unsigned pad0:1;
      unsigned grf_reg_count_1:3;
      unsigned pad1:2;
      unsigned kernel_start_pointer_1:26;
   } wm8;

   struct {
      unsigned pad0:1;
      unsigned grf_reg_count_2:3;
      unsigned pad1:2;
      unsigned kernel_start_pointer_2:26;
   } wm9;

   struct {
      unsigned pad0:1;
      unsigned grf_reg_count_3:3;
      unsigned pad1:2;
      unsigned kernel_start_pointer_3:26;
   } wm10;
};

struct gen5_sampler_default_color {
   uint8_t ub[4];
   float f[4];
   uint16_t hf[4];
   uint16_t us[4];
   int16_t s[4];
   uint8_t b[4];
};

#endif
