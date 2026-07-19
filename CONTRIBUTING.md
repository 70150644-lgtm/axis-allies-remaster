# Contributing to Axis & Allies Remaster

Thank you for your interest in contributing! This document provides guidelines for contributing to the project.

## Code of Conduct

Be respectful, inclusive, and professional in all interactions.

## Getting Started

### Prerequisites
- Unreal Engine 5.3+
- Visual Studio 2022
- Git
- 50GB+ disk space

### Setup
1. Clone the repository
2. Run GenerateProjectFiles.bat (Windows)
3. Open AxisAllies.sln in Visual Studio
4. Compile the project

## Development Workflow

### Branch Naming
- `feature/description` - New features
- `bugfix/description` - Bug fixes
- `refactor/description` - Code refactoring
- `docs/description` - Documentation

### Commit Messages
```
[TYPE] Brief description (50 chars max)

Detailed explanation (72 chars per line)

Fixes #123
```

### Pull Request Process
1. Create feature branch from main
2. Make changes with descriptive commits
3. Write tests
4. Submit PR with clear description
5. Address review feedback
6. Merge after approval

## Code Style Guide

### C++ Conventions
- Class names: `PascalCase`
- Member variables: `pascal` with prefix (Unreal convention)
- Functions: `PascalCase`
- Constants: `UPPER_SNAKE_CASE`

### Documentation
- Add comments for complex logic
- Use Doxygen-style function docs
- Update README for major changes

## Testing

All code changes should include tests.

## Questions?

- Check existing documentation
- Search closed issues
- Open a new issue

---

**Last Updated**: July 2026