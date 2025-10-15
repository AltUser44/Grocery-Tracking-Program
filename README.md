# CornerGrocer — Grocery Tracking Program

Version: project snapshot (Oct 15, 2025)

## Overview
CornerGrocer is a small C++ object‑oriented program to count grocery item frequencies from a text file, 
create a simple backup file, and provide interactive queries, a frequency listing, and an ASCII histogram. 
The codebase is intentionally simple and designed to be built with Visual Studio on Windows.

Key points
- Case‑insensitive counting (items normalized to lowercase).
- Object-oriented design: core frequency logic and higher-level program management are separated into classes.
- Input tokens are whitespace-delimited (single-word items). A sample data file `frequency.dat` is included.

## Project layout
- CornerGrocer_Project.sln — Visual Studio solution
- CornerGrocer_Project.vcxproj* — project files and filters
- src/project files:
  - GroceryTracker.h / GroceryTracker.cpp — low-level frequency map management (normalization, load/save, printing utilities)
  - GroceryManager.h / GroceryManager.cpp — higher-level manager that coordinates loading input, writing backup, and exposing methods used by main (menu operations)
  - main.cpp — interactive menu (text UI) that uses GroceryManager
  - frequency.dat — example input data
- .gitignore — ignores .vs, build outputs, and other IDE artifacts

## Design/architecture
- GroceryTracker (core)
  - Responsible for counting item frequencies using std::map<std::string, size_t>.
  - Normalizes item tokens to lowercase and trims whitespace.
  - Provides loading from a file, writing a simple backup file (one "item count" per line), and print helpers (frequency list and histogram).
- GroceryManager (manager)
  - Wraps GroceryTracker; responsible for initializing from the project input file, ensuring a backup (`frequency.dat`) is written, and exposing methods used by the interactive UI:
    - getFrequencyForItem(const std::string& item)
    - printFrequencyList()
    - printHistogram()
  - Keeps high-level program flow separate from the low-level counting logic.
- main.cpp
  - Provides a console menu:
    1) Get the frequency of a specific item
    2) Print frequency list for all items
    3) Print a histogram for all items
    4) Exit
  - Uses explicit types in function signatures and avoids implicit "auto" for public interfaces for clarity and portability.

## Public API (what the executable offers)
- Interactive menu (run the built exe and follow prompts).
- Programmatic API (class methods — see headers for exact signatures):
  - GroceryManager::GroceryManager(const std::string& inputFile, const std::string& backupFile)
  - int GroceryManager::getFrequencyForItem(const std::string& item) const
  - void GroceryManager::printFrequencyList() const
  - void GroceryManager::printHistogram() const
  - GroceryTracker::loadFromFile(const std::string& filename)
  - GroceryTracker::writeBackup(const std::string& filename) const
  - GroceryTracker::getFrequency(const std::string& item) const

(Refer to the header files for precise, up-to-date signatures.)

## Input format and behavior
- The program reads a text file of whitespace-separated tokens. Each whitespace-delimited token is treated as one item.
- Items are normalized to lowercase before counting, so queries are case-insensitive.
- Multi-word items (containing spaces) are currently not supported because input uses token-based reading.
- If you need multi-word items, change loading to line-based parsing or CSV.

## Build (Windows / Visual Studio)
1. Open `CornerGrocer_Project.sln` in Visual Studio (2019/2022).
2. Choose configuration (Debug/Release) and platform (x64/x86).
3. Build: Build → Build Solution.
4. The executable will be produced under a platform/config-specific output folder, e.g.:
   - `.\x64\Debug\CornerGrocer_Project.exe`

CLI build:
- msbuild CornerGrocer_Project.sln /p:Configuration=Release /p:Platform=x64

## Run / Usage examples
- From PowerShell (adjust path to the built exe):
  - `.\x64\Debug\CornerGrocer_Project.exe`
- The program will load `CS210_Project_Three_Input_File.txt` (project default) and write/overwrite `frequency.dat` as a backup.
- Follow the on-screen menu to query a single item (single-word), print a full frequency list, or show the histogram.

Example: Query a single item
- Choose menu option 1 and enter a single-word item like: apple
- Output: apple: 5

Example: Print histogram
- Choose menu option 3
- Output shows each item left-aligned with '*' repeated by its count.

## Notes, assumptions, and known limitations
- Tokenization: uses operator>> (whitespace delimited). Multi-word product names are split into multiple tokens.
- Unicode: current normalization uses std::tolower on unsigned char — sufficient for ASCII but not full Unicode case folding.
- Large counts: histogram prints one star per count; huge counts will produce long lines. Could you consider scaling if needed?
- Thread-safety: current implementation is single-threaded.
- Explicit signatures: public interfaces use explicit types (no auto in public method signatures) and main uses the conventional int main() signature.

## Testing & further development suggestions
- Add unit tests for GroceryTracker (loadFromFile, getFrequency, writeBackup) and GroceryManager (integration behavior).
- Improve parsing to support quoted/multi-word items or CSV input.
- Add command-line flags: input file path, backup path, show-only-frequency, show-only-histogram, or scale option for histograms.
- Consider switching to unordered_map for performance on large inputs (if ordering by name is not required).

## Git/repository tips
- Ensure `.vs/` is listed in `.gitignore`. If the `.vs` folder was previously committed:
  - git rm -r --cached .vs
  - git commit -m "Stop tracking .vs"
  - git push
- If the remote contains unknown commits, integrate them before pushing:
  - git fetch origin
  - git pull --rebase origin main
  - git push origin main

## License
- No license file included by default. Add an appropriate license (MIT, Apache 2.0, etc.) if you intend to publish this repository publicly.
- Owner AltUser44

## Contact/contribution
- For code changes: open a PR with a brief description, tests (if applicable), and build instructions.
- For small focused changes (e.g., support multi-word items), request a patch and indicate whether you prefer line-based parsing or CSV.
