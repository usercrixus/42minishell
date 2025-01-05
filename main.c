/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:02:50 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/05 05:58:06 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/prctl.h>
#include <sys/syscall.h>
#define PR_SET_CHILD_SUBREAPER 36

volatile sig_atomic_t g_command_running = 0;

int	main(int argc, char **argv)
{
    long ret;
    // Set this process as a subreaper
    //syscall(SYS_prctl, PR_SET_CHILD_SUBREAPER, 1, 0, 0, 0);

    __asm__ volatile (
        "movq %1, %%rax\n\t"  // System call number (prctl)
        "movq %2, %%rdi\n\t"  // First argument: PR_SET_CHILD_SUBREAPER
        "movq %3, %%rsi\n\t"  // Second argument: 1 (enable subreaper)
        "movq $0, %%rdx\n\t"  // Third argument: 0
        "movq $0, %%r10\n\t"  // Fourth argument: 0
        "movq $0, %%r8\n\t"   // Fifth argument: 0
        "syscall\n\t"         // Invoke system call
        "movq %%rax, %0"      // Store return value in ret
        : "=r"(ret)           // Output
        : "i"(SYS_prctl), "i"(PR_SET_CHILD_SUBREAPER), "i"(1) // Inputs
        : "rax", "rdi", "rsi", "rdx", "r10", "r8", "memory" // Clobbered
    );

	(void)argc;
	(void)argv;
	input_loop();
	return (0);
}
