/* SPDX-License-Identifier: GPL-2.0 */
/*
 * include/linux/arch_topology.h - arch specific cpu topology information
 */
#ifndef _LINUX_ARCH_TOPOLOGY_H_
#define _LINUX_ARCH_TOPOLOGY_H_

#include <linux/types.h>
#include <linux/percpu.h>

void topology_normalize_cpu_scale(void);
int topology_detect_flags(void);
int topology_smt_flags(void);
int topology_core_flags(void);
int topology_cpu_flags(void);
int topology_update_cpu_topology(void);

struct device_node;
bool topology_parse_cpu_capacity(struct device_node *cpu_node, int cpu);

DECLARE_PER_CPU(unsigned long, cpu_scale);

struct sched_domain;
static inline
unsigned long topology_get_cpu_scale(struct sched_domain *sd, int cpu)
{
	return per_cpu(cpu_scale, cpu);
}

void topology_set_cpu_scale(unsigned int cpu, unsigned long capacity);

DECLARE_PER_CPU(unsigned long, efficiency);
static inline
unsigned long topology_get_cpu_efficiency(int cpu)
{
	return per_cpu(efficiency, cpu);
}

DECLARE_PER_CPU(unsigned long, freq_scale);

static inline
unsigned long topology_get_freq_scale(struct sched_domain *sd, int cpu)
{
	return per_cpu(freq_scale, cpu);
}

DECLARE_PER_CPU(unsigned long, arch_min_freq_scale);

static inline unsigned long topology_get_min_freq_scale(int cpu)
{
	return per_cpu(arch_min_freq_scale, cpu);
}

void topology_set_min_freq_scale(const struct cpumask *cpus,
				 unsigned long min_freq, unsigned long max_freq);

DECLARE_PER_CPU(unsigned long, max_freq_scale);
DECLARE_PER_CPU(unsigned long, max_thermal_scale);

static inline
unsigned long topology_get_max_freq_scale(struct sched_domain *sd, int cpu)
{
	return min(per_cpu(max_freq_scale, cpu),
		   per_cpu(max_thermal_scale, cpu));
}

#endif /* _LINUX_ARCH_TOPOLOGY_H_ */
