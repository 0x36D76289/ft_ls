# ft_ls

A recreation of the Unix `ls` command written in C as part of the 42 curriculum.

![42 Logo](https://42.fr/wp-content/uploads/2021/05/42-Final-sigle-seul.svg)

## Description

This project implements a simplified version of the `ls` command, which lists directory contents. The implementation follows the 42 School coding standards and includes support for various command-line options.

## Features

The `ft_ls` program supports the following flags:

- **`-l`**: Long format display (detailed file information including permissions, links, owner, group, size, and modification time)
- **`-a`**: Show all files, including hidden files (starting with '.')
- **`-R`**: Recursive listing of subdirectories
- **`-r`**: Reverse the order of the sort
- **`-t`**: Sort by modification time (newest first)

## Building

To compile the project:

```bash
make
```

This will:
1. Compile the custom `libft` library
2. Compile all source files
3. Link everything to create the `ft_ls` executable

```bash
make clean
make fclean
make re
```

## Usage

```bash
./ft_ls [options] [file/directory...]
```

### Examples

```bash
# Basic listing
./ft_ls

# Long format
./ft_ls -l

# Show hidden files
./ft_ls -a

# Recursive listing
./ft_ls -R

# Multiple options
./ft_ls -la

# Sort by time in reverse order
./ft_ls -ltr

# List specific directories
./ft_ls -l /usr /tmp
```
