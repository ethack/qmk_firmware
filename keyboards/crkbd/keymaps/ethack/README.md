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
- https://www.reddit.com/r/olkb/comments/a0texz/whatre_your_favorite_qmk_hacks/
- https://www.keebtalk.com/t/show-me-your-favorite-qmk-hacks/2682/36
- https://docs.qmk.fm/#/feature_macros?id=super-alt%e2%86%aftab
- https://www.reddit.com/r/olkb/comments/7av182/could_i_please_have_some_help_with_simple/

# Problems
## Keymap
- Cheatsheet
- **A good percent of the time when I try to type - it comes out ' h'. Figure out why this is. Do I release the raise key too soon?**
     - I saw something about changing the TAPPING_TERM for a single key. Maybe this could help?
- In general I prefer my right hand to do things like navigation. Things that I can do there instead of with the mouse. But my left hand is useful for things I do in combination with the mouse (copy/paste, save, new tab, close tab, screenshot, volume controls) and I want to make sure those stay one handed.
- By combining ctl and tab on the same key I can't use that key combo.
- It would be very nice to have an auto repeat of my thumb backspace, but I won't give up the number shortcut. Maybe a double/triple tap and hold could be auto repeat.
    - Create a key that turns autoshift on/off.
- Would like shrug emoticon `¯\_(ツ)_/¯`
    - Had to enable Unicode in rules.mk. But that resulted in:
    ` * The firmware size is approaching the maximum - 27996/28672 (676 bytes free)`
    - Probably better way is to map to a hyper combo and use AutoKey
- I have problems finding the special characters still. Maybe it would be better to have them in more unique locations that are memorable.
- I can't use the windows key or function keys while on Windows (or anytime, but that's when I miss it).
    - I have a windows key in the edit layer, but that doesn't let me do key combos like for Regolith. Find a way to put the super key in the main layer or figure out a good different key to use.
    - Maybe I can replace the left space with a Windows key. Though that means re-learning the symbol layer trigger. This could move to enter since it's already there but I don't use that key.
    - For Regolith I'm looking at the shortcuts and I think I might need a special layer to do all these. For instance, accessing the numbers or arrows while holding down super is going to be a pain. Though I could just remap the shortcuts too like using hjkl instead of arrow keys or yuiop (top row right hand) for the numbers.
        - https://github.com/regolith-linux/regolith-desktop/wiki/Getting-Started
- I haven't messed with layers that stay put at all. I've only used key that change while holding another.
    - Numpad
- For gaming the "trigger space on keyup" is very annoying. All of the thumb keys will have problems because they either will trigger on keyup or there will be a delay for the held down function.
    - I should have a separate gaming layer that I can activate.
    - The only thing I should need the edit layer for in a game is the volume controls. Maybe I can move those to the shortcuts layer with the play/pause. (done)
- Right now the enter hold key is the symbol layer. But I never use this.


## Shortcuts to learn
- ctrl-backspace deletes a word. I think Textblade makes use of this and other similar ones.

## Keycaps
- Would really like homing keycaps for both home row and my thumbs. Possibly knurled keys or inverted angled caps for the thumb keys.

## Switches
- Turns out I'm not a huge fan of these Gateron brown switches. They are alright I guess and I should get used to them more.
- I think I would like box switches to get rid of some of the keycap wiggle.
- I don't think I like the tactile bump. Maybe I would like linear switches or possibly torpe switches. The actuation force seems a little high for my tastes too, but then again I think I've caught myself resting my fingers and accidentally hitting certain keys. I think the bump makes it feel like the keys are dirty and that I need to clean out the resistance.

## Accessories
- Tenting
- Wrist support


# Solutions
- Increased [`TAPPING_TERM`](https://docs.qmk.fm/#/config_options?id=behaviors-that-can-be-configured) to 200 and that did the trick!
    - My Hyper escape key doesn't work properly. The escape isn't registering. I'm unsure whether this is the actual key or the code. The hyper portion seems to work, so it's just the escape that doesn't.
    - My right shift key has to be pressed ultra hard to register. I may need to resolder something. Testing The Right Shift Key. That Seems to Work so I Wonder why the parenthesis is not. Oh, it seems like the left is the same way and it's just a timing value that I need to tweak. I'm holding the key too long so it registers as shift instead when I want parenthesis.
- When using the `LT()` macro, I needed to use `_LAYER` instead of `LAYER` since the underscore is the layer number and the non-underscore is the keycode which gets randomized.
    - Reuse keys like raise, lower, space, and enter when held. I also keep messing up space and enter now. Maybe the solution is to make the two small keys space on tap, the two big keys enter on tap, and the right act as raise and the left act as lower on tap. No, that won't help because I've been wanting to hit the big right key as a space too. Wait, yeah because I can just use the normal space key as a raise. I'll give it a shot.
    - I think over time I'll probably use my right thumb for both enter and space. That means I can use the left two thumb keys for something different on tap.
- Volume controls aren't working.
    - Needed `EXTRAKEY_ENABLE` in the rules.mk file.
- () are duplicated on the raise layer due to SpaceCadet usage.
    - Removed () and have been using shift just fine.
- Would like backspace on the number layer too. But the I need a place for delete. Shift delete might work ok. I just reached for that by instinct.
    - https://www.reddit.com/r/olkb/comments/4u36wk/qmk_question_how_do_i_make_backspace_send_delete/
    - https://github.com/qmk/qmk_firmware/issues/61
    - Delete is on the edit later now instead and backspace on number layer.
- I think I'd really like d/f to trigger the arrow keys. I keep hitting d expecting that to do the job and it doesn't. It seems like this would be pretty hard to do.
    - https://www.reddit.com/r/olkb/comments/8eticz/how_to_activate_a_layer_with_a_combination/
    - I've gotten used to movement with the thumb key activating the edit layer.
- Add a bunch of other special keys to the raise layer. Things like favorites, calculator, back, forward, play/pause.
    - I have a special shortcuts layer now.
- Would be nice to have shortcuts for switching desktops. Though maybe I should figure out what the OS shortcuts are first haha.
    - On the shortcut layer.
- I tried to keep any keys I'd already gotten used to in the same place and tried to keep keys between layers the same as well when it made sense.
- Access to [] and {}, -_, |\, and really all special characters. May just take some getting used to.
- It would be nice to have a tab key easier to reach. Maybe that can go under my left thumb. Escape might go well there too.
- Set up textblade like keymap for copy,cut,paste and combo keys. KC_COPY and friends exist. Those keycodes don't seem to work on linux. Try mapping them to the right key combo.
- Missing equals from keymap.
- For left thumb cluster try: lctl/tab, space/edit, bspc/num
- Typing IPs on the number layer is really difficult due to the period placement. I think I should shift the numberpad over one even if it doesn't make the lining up so nice.
- I often need to put in a space when I use the mouse to place the cursor. There's no space on the left hand anymore.
    - Space is on both halves now.
- Autoshift also gets in the way of holding down the jk keys in vim.  I miss that the most and I'm not sure I use the autoshift feature anyway. I instinctually reach for the shift key. But I think I could train myself to use it. But I don't have any other use for the shift keys then right now and they work well as ().
    - Disabled autoshift.
- Sometimes I hold the number pad keys too long and get the shifted keys. Switch these to the numberpad keycodes.
    - Should be taken care of by disabling auto-shift.
- My pinky gets too tired hitting backspace all the time. Remap this to something else.
    - It is now '-'
    - I use - quite a bit. I wonder if I could have it on my default layer somewhere. Maybe LALT or BKSP.
    - Will try backspace first and see how that goes. But LALT might be better as I don't already have muscle memory for that one.
- **I rarely use the LALT key under my right thumb.** Also, this key doesn't have a second function. Maybe backspace or delete? Or another tab?
    - This is now delete on press and LALT on hold. I use LALT for alt-tab more often now.
- Be able to hold delete or backspace.
    - Put these on edit and symbol layers.
