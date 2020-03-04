# Concurrency Patterns
Here, we go through a few packages and review how they use concurrency.

## Runner
This package monitors running programs and can terminate them if they run for too long.

```go
type Runner struct {
  interrupt chan os.Signal
  complete chan error
  timeout <-chan time.Time
  tasks[]func(int)
}
```
This starts off with a declaration of a `Runner` struct which declares three channels to manage the lifecycle of a program, and a slice of functions that represent the different tasks.