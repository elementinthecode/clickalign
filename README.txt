Click Align - Geode mod source

Option A (no installs, builds online):
 1. Create a free GitHub repo and upload everything in this folder
    (keep the .github folder).
 2. Open the repo's Actions tab, run "Build Geode Mod" (or just push to main).
 3. When it finishes, download "Build Output" -> inside is the .geode file.
 4. Put the .geode in your Geometry Dash "geode/mods" folder.

Option B (local): run `geode build` in this folder (needs Geode CLI + Visual Studio Build Tools).

Edit "id" and "developer" in mod.json first, and set "geode"/"gd" versions to match yours.
