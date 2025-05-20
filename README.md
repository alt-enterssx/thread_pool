# Pool Tasker - Minimalist Thread Pool Library

**Pool Tasker** is a lightweight header-only C++17 thread pool implementation designed for efficient parallel task execution with zero external dependencies.

![Project Banner](/assets/banner.jpg)
## Classes

### PT::task
Represents an executable task unit with status tracking.

#### Constructors
| Signature | Description |
|-----------|-------------|
| `task()` | Default constructor |
| `task(F&& f, uint8_t id, Args&&... args)` | Creates task with callable and arguments |

#### Methods
| Method | Returns | Description |
|--------|---------|-------------|
| `set_id(uint8_t id)` | `void` | Sets task identifier |
| `get_id()` | `uint8_t` | Gets task identifier |
| `execute()` | `void` | Executes the task |
| `get_status()` | `task_status` | Returns current status |

#### Members
| Member | Type | Description |
|--------|------|-------------|
| `id` | `uint8_t` | Task identifier |
| `status` | `task_status` | Execution state |
| `executor` | `function<void()>` | Wrapped callable |

### PT::pool_task
Manages thread pool and task queue.

#### Constructor
| Signature | Description |
|-----------|-------------|
| `pool_task(int threads_cnt)` | Creates thread pool with specified size |

#### Methods
| Method | Returns | Description |
|--------|---------|-------------|
| `add_task(PT::task&& task)` | `void` | Enqueues task |
| `wait()` | `void` | Blocks until completion |
| `stop()` | `void` | Graceful shutdown |

#### Internal
| Component | Type | Purpose |
|-----------|------|---------|
| `threads` | `vector<thread>` | Worker threads |
| `tasks` | `deque<PT::task>` | Task queue |
| `mtx` | `mutex` | Queue lock |
| `cv` | `condition_variable` | Thread sync |
| `stop_fg` | `bool` | Shutdown flag |

## Enums
### task_status
| Value | Description |
|-------|-------------|
| `complete` | Task finished |
| `in_queue` | Task queued |

## Authors

- [@atlenter](https://www.github.com/alt-enterssx)


## Feedback

If you have any feedback, please reach out to us at altenter.codi@gmail.com

