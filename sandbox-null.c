/* $OpenBSD$ */
/*
 * Copyright (c) 2011 Damien Miller <djm@mindrot.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "includes.h"

#include <sys/types.h>

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "log.h"
#include "ssh-sandbox.h"
#include "xmalloc.h"

/* dummy sandbox */

struct ssh_sandbox {
	int junk;
};

static int
sandbox_null_probe(void)
{
	return 1;
}

static void *
sandbox_null_init(void)
{
	struct ssh_sandbox *box;

	/*
	 * Strictly, we don't need to maintain any state here but we need
	 * to return non-NULL to satisfy the API.
	 */
	box = xcalloc(1, sizeof(*box));
	return box;
}

static void
sandbox_null_child(void *vbox)
{
	/* Nothing to do here */
}

static void
sandbox_null_parent_finish(void *vbox)
{
	free(vbox);
}

static void
sandbox_null_parent_preauth(void *box, pid_t child_pid)
{
	/* Nothing to do here */
}

Sandbox ssh_sandbox_null = {
	"null",
	sandbox_null_probe,
	sandbox_null_init,
	sandbox_null_child,
	sandbox_null_parent_finish,
	sandbox_null_parent_preauth
};
