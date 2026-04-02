# Installation

`cordic` can be installed from PyPI, GitHub, or built from source.

---

## Prerequisites

- **Python 3.10+**
- **NumPy** (installed automatically as a dependency)

For source builds you additionally need:

- A C compiler (`gcc` or `clang`)
- `meson` and `meson-python` build system
- `numpy` (for `f2py` compilation)

## [PyPI](https://pypi.org/project/cordic)

For using the PyPI package in your project, add the following to your
configuration file:

=== "pyproject.toml"

    ```toml
    [project]
    dependencies = [
        "cordic"
    ]
    ```

=== "requirements.txt"

    ```text
    cordic
    ```

### pip

```bash
pip install --upgrade cordic
```

### uv

```bash
# Add to a uv project
uv add cordic

# Or install into the current environment
uv pip install cordic
```

### pipenv

```bash
pipenv install cordic
```

### poetry

```bash
poetry add cordic
```

### pdm

```bash
pdm add cordic
```

### hatch

```bash
hatch add cordic
```

## [git](https://github.com/eggzec/cordic)

Install the latest development version directly from the repository:

```bash
pip install --upgrade "git+https://github.com/eggzec/cordic.git#egg=cordic"
```

### Building locally

Clone and build from source to modify the C code or test local changes:

```bash
git clone https://github.com/eggzec/cordic.git
cd cordic
uv pip install .
```

This invokes the `meson` build system to compile the C sources via `f2py`
and install the resulting extension module.

!!! warning "C compiler required"
    Source builds require a working C compiler.

    ```bash
    # Debian/Ubuntu
    sudo apt install gcc

    # Fedora
    sudo dnf install gcc

    # macOS (Clang via Xcode Command Line Tools)
    xcode-select --install
    ```

    On Windows, install MSVC via Visual Studio Build Tools. MinGW is not supported.

## Verifying the installation

After installation, verify that the package loads correctly:

```python
import cordic

print(cordic.cos(1.0))    # ≈ 0.5403
print(cordic.sqrt(2.0))   # ≈ 1.4142
print("cordic is working!")
```

## Dependencies

- Python >=3.10
- [numpy](https://pypi.org/project/numpy)
