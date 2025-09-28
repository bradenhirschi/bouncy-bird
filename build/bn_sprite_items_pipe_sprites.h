#ifndef BN_SPRITE_ITEMS_PIPE_SPRITES_H
#define BN_SPRITE_ITEMS_PIPE_SPRITES_H

#include "bn_sprite_item.h"

//{{BLOCK(pipe_sprites_bn_gfx)

//======================================================================
//
//	pipe_sprites_bn_gfx, 128x64@4, 
//	+ palette 16 entries, not compressed
//	+ 128 tiles Metatiled by 4x8 not compressed
//	Total size: 32 + 4096 = 4128
//
//	Time-stamp: 2025-09-28, 10:26:31
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PIPE_SPRITES_BN_GFX_H
#define GRIT_PIPE_SPRITES_BN_GFX_H

#define pipe_sprites_bn_gfxTilesLen 4096
extern const bn::tile pipe_sprites_bn_gfxTiles[128];

#define pipe_sprites_bn_gfxPalLen 32
extern const bn::color pipe_sprites_bn_gfxPal[16];

#endif // GRIT_PIPE_SPRITES_BN_GFX_H

//}}BLOCK(pipe_sprites_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item pipe_sprites(sprite_shape_size(sprite_shape::TALL, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(pipe_sprites_bn_gfxTiles, 128), bpp_mode::BPP_4, compression_type::NONE, 4), 
            sprite_palette_item(span<const color>(pipe_sprites_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

