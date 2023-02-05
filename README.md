# SC24 Training Camp
## Multi Node Manager _Slurm_ & $\pi$ Calculation

2/6. `nevikw39`.

> [_Taiwania 3_ Manual](https://man.twcc.ai/@TWCC-III-manual/H1bEXeGcu)

## Multi Node Manager _Slurm_

### Cluster Computer

In practical, most supercomputers are clusters of [computation nodes](https://man.twcc.ai/@TWCC-III-manual/B1XNOLouO), each of which is equipped with CPU, main memory, ... Among the nodes, they're interconnected by _Ethernet_ or _InfiniBand_. [File system](https://man.twcc.ai/@TWCC-III-manual/HyOgKIiuu) is usually shared by nodes, even other cluster.

Generally, **computation nodes** would not have access to the Internet. On the other hand, we could connect to **login nodes**, submitting jobs or doing lightweight tasks there. Moreover, there are [**data transfer node**](https://man.twcc.ai/@TWCC-III-manual/SyGsFqRSt) dedicated to uploading or downloading files via `SFTP` or similar mechanisms.

It is parallel programming that makes the whole use of supercomputers.

### Slurm

> Simple Linux Utility for Resource Management

Since there are quite a few computation nodes, it's necessary for us to have a manager to coordinate the resources.

The jobs could be categorizeed into two types: interactive and non-interactive ones. Interactive jobs are launched through the shells, whereas the non-interactive ones would be batched in background.

In [_Slurm_](https://man.twcc.ai/@TWCC-III-manual/H1Bx15sd_), there are some [partitions](https://man.twcc.ai/@TWCC-III-manual/ryyo0tsuu) containing computation nodes served as queues that accept jobs. On _Taiwania 3_, the difference among partitions is the number of CPU cores. On _Taiwania 2_, the difference is the wall time.

There are several [_Slurm_ commands](https://man.twcc.ai/@TWCC-III-manual/rysztb9id). I would casually divide them into two groups:

- Info
  - `squeue`: Show the status of running and pending jobs. Use `squeue -u $USER` to list your own jobs only.
  - `sinfo`: Show the status of nodes and partitions. To see the summary of partitions, use `sinfo -s`.
  - `scontrol`, `sacct`, `sstat`, ...
- Job
  - `sbatch`: Submit non-interactive jobs.
  - `salloc`: Request resources (for interactive jobs mostly).
  - `srun`: Launch the parallel job within the resource (Allocate if necessary).
  - `scancel`: Kill the job that is not yet completed. When something goes into trouble, stop all of your jobs by `scancel -u $USER`.

All jobs should be associated with a **account** with enough **service unit** (SU). On `Taiwania`, one's accounts could be shown by the command `wallet`.

The most vital resource that we're concerned is the number of CPU cores. Normally, it's enough for us to determine the number of total tasks / MPI ranks / processes. Nonetheless, we could also limit the maximum number of nodes in used or the tasks per node.

$$\mathtt{\$SLURM\\_NTASKS}\leq\mathtt{\$SLURM\\_NNODES}\times\mathtt{\$SLURM\\_NTASKS\\_PER\\_NODE}$$

Prons and cons of interactive and non-interactive jobs:
- Flexibility
- Real-time feedback or not
- Resource utilization
- Batch processing or human interactions

#### Interactive Jobs

To start an interactive job, request resources by `salloc` and launch the pseudo terminal (pseudo TTY, PTY) by `srun`.

```bash
salloc -A $ACCOUNT_NAME -p $PARTITION -n $N srun --pty bash
```

Remember to quit since that it costs every second even if idling!

#### Non-Interactive Jobs

```bash
sbatch -A $ACCOUNT_NAME -p $PARTITION -n $N $COMMANDS
```

When we have more options and commands, it'd be better put all stuff into a [script](https://man.twcc.ai/@TWCC-III-manual/Sy9-QqHiO) and submit the job in shorter form:
```bash
sbatch $SCRIPT
```

In which the script is a bash script like the following one:
```bash
#!/bin/bash

#SBATCH -J pi-mt               # Job Name
#SBATCH -A GOV111082           # Account
#SBATCH -p ct2k                # Partition
#SBATCH -o mt_out_%j.log       # Redirect `stdout` to File
#SBATCH -e mt_err_%j.log       # Redirect `stderr` to File

#SBATCH -n 1000                # `--ntasks`, number of tasks / MPI ranks / processes                                 $SLURM_NTASKS
#
# #SBATCH -c 1                 # `--cpus-per-task`, number of cores / threads **per** tasks / MPI ranks / processes. $SRUN_CPUS_PER_TASK
# #SBATCH -N 18                # `--nodes`, number of **minimium** nodes!!                                           $SLURM_NNODES
# #SBATCH --ntasks-per-node=56 # number of **minimium** tasks / MPI ranks / processes per nodes!!                    $SLURM_NTASKS_PER_NODE
#
# $SLURM_NTASKS <= $SLURM_NNODES * $SLURM_NTASKS_PER_NODE

ml purge
# srun ...
```
Note that the shebang is necessary. `sbatch` seems to launch the job by that.

## $\pi$ Calculation

> https://news.ltn.com.tw/news/novelty/breakingnews/3954858

$\pi$ is a irrational, transcendental mathematical constant that plays a crucial role in not only math but also many other science fields. In addition, $\pi$ has plenty of intriguing properties.

In pratical, we often approximate $\pi$ by:

- $3.1415926\dots$
- $4\arctan1$

The history that people tried to computes $\pi$ dates back to a long time ago. Even though it's of little use to reach extreme accuracy, people still have fun in this errand.

Nowadays, there are some common approaches to caculate the value of $\pi$:

0. **Monte Carlo** method
   - ![](https://upload.wikimedia.org/wikipedia/commons/8/84/Pi_30K.gif)
   - This figure was adopted from [Wikipedia](https://en.wikipedia.com/wiki/Approximations_of_%CF%80).
1. **Gregory–Leibniz** series, e.g., $\arctan$ at $1$ would be $\displaystyle1-\frac{1}{3}+\frac{1}{5}-\frac{1}{7}+\dots=\sum_{k=0}^\infty\frac{(-1)^k}{2k+1}$
2. **Integral** of some functions, e.g.,
   - $4\int_0^1\sqrt{1-x^2}dx$
   - $4\int_0^1\frac{1}{1+x^2}dx$

Any of the above ways requires quite a few iterations to attain the desired precision. As a consequence, this task becomes a really good example to illustrate the power of parallel programming and HPC.

### MPI Programming

By default, there are `GCC 4.8.5` and `Open MPI 4.0.3` on _Taiwania 3_. In this template, we could use `make all CC=mpicc` to build the binaries. To launch the **MPI** programs, for **MPI** with PMI libraries, e.g., **Open MPI**, `srun` would be more convenient; for **Intel MPI** which wasn't built with PMI, we should call `mpiexec.hydra -bootsrap slurm`, or shortly `mpirun`.

#### Various Combinations

There are many modules of different versions of compilers on _Taiwania 3_, to which there would be some implementations of MPI corresponding. Nevertheless, there are several pitfalls within.

For instance, the UCX config `UCX_NET_DEVICES` was incorrectly set by **Intel MPI** for Intel Compiler 2022 and **Open MPI** for GCC 10.2.0. Please refer to the job scripts provided.

## Hands-on Labs!!

0. Modify the simple job script and submit it.
   - Check out different numbers of tasks / MPI ranks / processes!!
1. Rewrite `pi_integral.c` with MPI multiprocessing.
   Design your job script for it based on the templates provided.
2. Try and observe the wall time of different compiler & MPI combinations.

## MISC.

Windows users _no longer need_ `MobaXTerm` since Windows 10 has built-in `OpenSSH` client. For the `X11` apps, one might install a `X11` server, or **WSLg**[^WSLg] would be of help. BTW, Windows Terminal looks far more delightful than the default terminal.

### VS Code Remote Tunnel

Run a [VS Coder server](https://code.visualstudio.com/blogs/2022/07/07/vscode-server#_a-preview-of-a-larger-journey) on _Taiwania_ so that we could connect to it via VS Code avoiding annoying OTP.

0. Log into _Taiwania_ with your password and OTP.
1. 
   ```bash
   mkdir -p ~/.local/bin
   wget -O ~/.local/bin/code-server https://aka.ms/vscode-server-launcher/x86_64-unknown-linux-musl
   ```
2. We need run the server in background even though current session is closed. So type `tmux` to create a session. Then run `code-server`.
3. For the first time, open [GitHub Device Activation](https://github.com/login/device) (this link would appear in the terminal) in your browser and enter the code in the terminal.
4. Now we could detach from the `tmux` seesion. Press <kbd>⌃Ctrl</kbd> $+$ <kbd>B</kbd>, then <kbd>D</kbd>.
5. In your VS Code, update to at least $1.73$ and install the _Remote Tunnels_ extension. Click the left-bottom corner and then connect to the tunnel. You might be required to log into your GitHub account. Voilà!

[^WSLg]: All you have to do is to update Windows and WSL. Here is official [tutorial](https://learn.microsoft.com/en-us/windows/wsl/tutorials/gui-apps).
