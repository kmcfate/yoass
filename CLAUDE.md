# CLAUDE.md

This file provides guidance for AI assistants (e.g., Claude Code) working in this repository.

## Project Overview

**yoass** (Your Only Assistant) is currently an early-stage project. The repository contains only a LICENSE (Apache 2.0) and README. No source code, dependencies, or build tooling exist yet.

## Repository State

```
yoass/
├── LICENSE        # Apache License 2.0
├── README.md      # Minimal project description
└── CLAUDE.md      # This file
```

## Branches

- `master` / `main` — primary branch
- Feature branches follow the pattern `claude/<description>-<id>`

## Development Guidelines

Since no language or framework has been chosen yet, follow these general principles when adding code:

### Starting Development

Before writing any code, establish:
1. The target language/runtime
2. A `package.json`, `requirements.txt`, `Cargo.toml`, or equivalent
3. A basic directory structure (`src/`, `tests/`, `docs/`)
4. Linting and formatting configuration

### Conventions to Adopt (when applicable)

- Keep source code under `src/`
- Keep tests alongside source or under `tests/`
- Document public APIs and modules
- Prefer explicit configuration over hidden magic
- Use environment variables for secrets — never commit credentials

### Git Workflow

- Develop on feature branches named `claude/<description>-<id>`
- Write clear, descriptive commit messages
- Push with `git push -u origin <branch-name>`
- Do not push to `master`/`main` directly without a review

## License

Apache License 2.0 — see [LICENSE](./LICENSE) for details.
