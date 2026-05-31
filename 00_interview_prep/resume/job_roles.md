
# The RISC-V Software Engineer (Staff) position at Qualcomm

https://qualcomm.wd12.myworkdayjobs.com/External/job/Bangalore-IND/RISC--V-Software-Engineer-Staff_3089120?shared_id=NjA3ZjBjYmItZTNlNi00ZTFiLTk2NTItNmZkMDA3Nzk4OGRh

Here is a targeted roadmap to acquire the specific skills required for this role:

Phase 1: Core Virtualization and SecurityConfidential Compute: The role heavily demands knowledge of Trusted Execution Environments (TEE), ARM CCA, and RISC-V CoVE. Designing end-to-end Secure Boot systems provides a massive advantage here; the logical next step is exploring how hypervisors isolate these secure enclaves using hardware virtualization extensions.  Linux KVM: Moving from upper-layer boot processes and RTOS implementations (like Zephyr) into the Linux Kernel space is the most critical technical bridge to cross. Set up a RISC-V or ARM emulation platform using QEMU to study how Linux KVM handles memory virtualization and vCPU scheduling.

Phase 2: Tooling and System ValidationAdvanced System Debugging: The job requires deep proficiency with Linux-specific tools like ftrace, perf, kgdb, and crash. Expanding upon existing system-level crash dump architectures by integrating these native kernel tools will directly fulfill this requirement.CI/CD & Containerization: Familiarity with Docker and continuous integration pipelines is explicitly listed. You can master this quickly by automating the compilation, deployment, and testing of custom KVM-enabled kernel builds within Docker containers.

Phase 3: Open-Source EngagementUpstreaming Patches: A major differentiator for this Staff-level role is a proven track record of working with the Linux KVM or broader kernel community. Engaging with RISC-V or Linux mailing lists and actively proposing specification changes or submitting patches is mandatory for this level.
