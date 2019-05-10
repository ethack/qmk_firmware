
# Reference
- https://docs.qmk.fm/#/keycodes
    - https://docs.qmk.fm/#/feature_audio
- https://docs.qmk.fm/#/feature_advanced_keycodes
    - https://docs.qmk.fm/#/feature_advanced_keycodes?id=switching-and-toggling-layers
    - https://docs.qmk.fm/#/feature_advanced_keycodes?id=modifier-keys
    - https://docs.qmk.fm/#/feature_advanced_keycodes?id=mod-tap
- https://config.qmk.fm/#/crkbd/rev1/LAYOUT
- https://thomasbaart.nl/category/mechanical-keyboards/firmware/qmk/
- https://jayliu50.github.io/qmk-cheatsheet/

# Features in use now
- https://docs.qmk.fm/#/feature_space_cadet
- Hyper Key `HYPR_T(KC_ESC)`
- https://docs.qmk.fm/#/feature_auto_shift?id=auto-shift-why-do-we-need-a-shift-key


# Features to try later
- https://docs.qmk.fm/#/feature_dynamic_macros
- https://docs.qmk.fm/#/feature_leader_key
    - https://thomasbaart.nl/2018/12/20/qmk-basics-leader-key/
    - https://docs.qmk.fm/#/feature_macros
- https://docs.qmk.fm/#/feature_tap_dance
    - https://thomasbaart.nl/2018/12/13/qmk-basics-tap-dance/
- https://docs.qmk.fm/#/feature_combo
    - https://waytools.rocks/keyboards/maps/qwerty
    - https://waytools.rocks/keyboards/maps/colemak
- https://waytools.rocks/keyboards/maps/emoji
- SpaceFn
    - https://www.reddit.com/r/MechanicalKeyboards/comments/6mzayi/with_qmk_or_tmk_can_i_have_the_spacebar_switch_to/

# Problems
- Access to [] and {}, and really all special characters. May just take some getting used to.
- () are duplicated on the raise layer due to SpaceCadet usage.
- Numberpad
- Tenting
- Wrist support
- Cheatsheet
- Would really like homing keycaps for both home row and my thumbs.
- Add a bunch of other special keys to the raise layer. Things like favorites, calculator, back, forward, play/pause.
- Set up textblade like keymap for copy,cut,paste and combo keys. KC_COPY and friends exist.


# Solutions
- Increased [`TAPPING_TERM`](https://docs.qmk.fm/#/config_options?id=behaviors-that-can-be-configured) to 200 and that did the trick!
    - My Hyper escape key doesn't work properly. The escape isn't registering. I'm unsure whether this is the actual key or the code. The hyper portion seems to work, so it's just the escape that doesn't.
    - My right shift key has to be pressed ultra hard to register. I may need to resolder something. Testing The Right Shift Key. That Seems to Work so I Wonder why the parenthesis is not. Oh, it seems like the left is the same way and it's just a timing value that I need to tweak. I'm holding the key too long so it registers as shift instead when I want parenthesis.
- When using the `LT()` macro, I needed to use `_LAYER` instead of `LAYER` since the underscore is the layer number and the non-underscore is the keycode which gets randomized.
    - Reuse keys like raise, lower, space, and enter when held. I also keep messing up space and enter now. Maybe the solution is to make the two small keys space on tap, the two big keys enter on tap, and the right act as raise and the left act as lower on tap. No, that won't help because I've been wanting to hit the big right key as a space too. Wait, yeah because I can just use the normal space key as a raise. I'll give it a shot.
    - I think over time I'll probably use my right thumb for both enter and space. That means I can use the left two thumb keys for something different on tap.
- Volume controls aren't working.
    - Needed `EXTRAKEY_ENABLE` in the rules.mk file.
