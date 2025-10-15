# CornerGrocer — Grocery Tracking Program

Summary
- Small C++ utility to track grocery item frequencies and display reports (frequency list and histogram).
- Counts are case-insensitive and stored in a map<string,size_t>.
- Intended to be built with Visual Studio on Windows (solution and vcxproj included).

Quick features
- Load items from a whitespace-separated text file and increment counts.
- Persist a simple backup file with "item count" lines.
- Print a formatted frequency list and an ASCII histogram.
- Example data file in the repo: `frequency.dat`

Repository layout
- CornerGrocer_Project.sln — Visual Studio solution
- CornerGrocer_Project.vcxproj* — project files
- GroceryTracker.h / GroceryTracker.cpp — core tracker implementation
  - Normalizes items to lowercase.
  - Uses `operator>>` tokenization (splits on whitespace).
  - `printFrequencies()` and `printHistogram()` print human-readable reports.
- main.cpp — program entry (builds and uses GroceryTracker; run to exercise functionality)
- frequency.dat — sample input
- .gitignore — ignores .vs, build artifacts, etc.

Build (Windows / Visual Studio)
1. Open `CornerGrocer_Project.sln` in Visual Studio 2019/2022.
2. Select configuration (Debug or Release) and target (x64/x86).
3. Build the solution (Build → Build Solution).
4. The executable will be in the project's output folder, e.g.:
   - `.\x64\Debug\CornerGrocer_Project.exe`
   - or `.\x64\Release\CornerGrocer_Project.exe`

Build (CLI)
- Using MSBuild:
  - msbuild CornerGrocer_Project.sln /p:Configuration=Release /p:Platform=x64
- After building, run the produced exe as below.

Run / Usage
- Basic idea (adjust path to built exe and input file):
  - PowerShell:
    - `.\x64\Debug\CornerGrocer_Project.exe frequency.dat`
  - If the program expects interactive commands, run the exe without arguments and follow prompts.
- Output:
  - Frequency list: item names (left-aligned) with counts.
  - Histogram: each item followed by `*` repeated count times.

Design notes/implementation details
- Data structure: std::map<std::string, size_t> (ordered by item name).
- Normalization: items trimmed and lowercased before counting (`toLowerCopy()`).
- Input reading: current code uses `operator>>` which treats whitespace as a separator — multi-word items (e.g., "green apple") will be split into tokens.
- Histogram printing: prints one `*` per count. Very large counts will produce long lines.
- Files:
  - `loadFromFile(filename)` — clears existing map and loads tokens from file.
  - `writeBackup(filename)` — writes lines "item count".
  - `getFrequency(item)` — returns the frequency (case-insensitive lookup).

Known issues/suggestions
- Multi-word items are not preserved (tokenization by whitespace). If you need multi-word item support, change input to read lines and parse differently (e.g., CSV or quoted strings).
- Very large counts will make the histogram hard to read. Consider scaling or buckets if counts can be large.
- If performance on large inputs matters, consider unordered_map for O(1) average lookup.
- Non-ASCII characters: current lowercasing uses tolower on unsigned char, which is fine for ASCII, but not for full Unicode case folding.
- Ensure `.vs/` is in `.gitignore` (already present); if `.vs` is tracked, run `git rm -r --cached .vs` then commit.

How to contribute
- Create an issue describing the change.
- Fork and submit a PR with a clear description and tests (if applicable).
- Follow the existing code style and add comments for non-obvious logic.

Development TODOs (optional)
- Support multi-word items (line-based parsing, CSV).
- Add command-line flags:
  - specify input file
  - choose between frequency list and histogram
  - scale histogram output
- Add unit tests for GroceryTracker methods.
- Add an option to persist/restore map using JSON or binary format.

Sample commands
- Create .gitignore, remove tracked .vs and commit (PowerShell):
  - git rm -r --cached .vs
  - git add.
  - git commit -m "Remove .vs and ignore IDE artifacts"
- Build and run:
  - Open solution in Visual Studio → Build → Run
  - or CLI: `msbuild CornerGrocer_Project.sln /p:Configuration=Debug /p:Platform=x64`

License
- This repository does not include a license file by default. Add a license (e.g., MIT) if you intend this to be open source.
- Owner AltUser44

Contact/support
- For specific changes, request small, focused updates (example: "add multi-word item support" or "add CLI flags") and a code snippet or test you
