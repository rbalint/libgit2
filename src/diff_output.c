#include "filter.h"
	return (digits > 0) ? GIT_SUCCESS : GIT_ENOTFOUND;
	int err = GIT_SUCCESS;
		if (bufs[0].ptr[0] == '@') {
			const char *scan = bufs[0].ptr;
			if (!(err = read_next_int(&scan, &range.old_start)) && *scan == ',')
				err = read_next_int(&scan, &range.old_lines);
			if (!err &&
				!(err = read_next_int(&scan, &range.new_start)) && *scan == ',')
				err = read_next_int(&scan, &range.new_lines);
			if (!err && range.old_start >= 0 && range.new_start >= 0)
				err = info->hunk_cb(
					info->cb_data, info->delta, &range, bufs[0].ptr, bufs[0].size);
		}
	else if ((len == 2 || len == 3) && info->line_cb) {
		err = info->line_cb(
			info->cb_data, info->delta, origin, bufs[1].ptr, bufs[1].size);
		if (err == GIT_SUCCESS && len == 3) {
			err = info->line_cb(
	return err;
static int set_file_is_binary_by_attr(git_repository *repo, git_diff_file *file)
	int error = git_attr_get(repo, file->path, "diff", &value);
	if (error != GIT_SUCCESS)
		return error;
	return error;
static void set_delta_is_binary(git_diff_delta *delta)
	if ((delta->old_file.flags & GIT_DIFF_FILE_BINARY) != 0 ||
		(delta->new_file.flags & GIT_DIFF_FILE_BINARY) != 0)
	else if ((delta->old_file.flags & GIT_DIFF_FILE_NOT_BINARY) != 0 ||
			 (delta->new_file.flags & GIT_DIFF_FILE_NOT_BINARY) != 0)
	int error, mirror_new;
	if ((git_off_t)((size_t)delta->old_file.size) != delta->old_file.size ||
		(git_off_t)((size_t)delta->new_file.size) != delta->new_file.size)
		delta->old_file.flags |= GIT_DIFF_FILE_BINARY;
		delta->new_file.flags |= GIT_DIFF_FILE_BINARY;
		return GIT_SUCCESS;
		delta->old_file.flags |= GIT_DIFF_FILE_NOT_BINARY;
		delta->new_file.flags |= GIT_DIFF_FILE_NOT_BINARY;
		return GIT_SUCCESS;
	error = set_file_is_binary_by_attr(diff->repo, &delta->old_file);
	if (error != GIT_SUCCESS)
		return error;
	mirror_new = (delta->new_file.path == delta->old_file.path ||
				  strcmp(delta->new_file.path, delta->old_file.path) == 0);
		delta->new_file.flags &= (delta->old_file.flags & BINARY_DIFF_FLAGS);
		error = set_file_is_binary_by_attr(diff->repo, &delta->new_file);
	set_delta_is_binary(delta);
	git_buf search;
	git_text_stats stats;

	if ((delta->old_file.flags & BINARY_DIFF_FLAGS) == 0) {
		search.ptr  = old_data->data;
		search.size = min(old_data->len, 4000);

		git_text_gather_stats(&stats, &search);

		if (git_text_is_binary(&stats))
			delta->old_file.flags |= GIT_DIFF_FILE_BINARY;
			delta->old_file.flags |= GIT_DIFF_FILE_NOT_BINARY;
	if ((delta->new_file.flags & BINARY_DIFF_FLAGS) == 0) {
		search.ptr  = new_data->data;
		search.size = min(new_data->len, 4000);

		git_text_gather_stats(&stats, &search);

		if (git_text_is_binary(&stats))
			delta->new_file.flags |= GIT_DIFF_FILE_BINARY;
			delta->new_file.flags |= GIT_DIFF_FILE_NOT_BINARY;
	set_delta_is_binary(delta);
	return GIT_SUCCESS;
	int error;

		return GIT_SUCCESS;
	if ((error = git_blob_lookup(blob, repo, oid)) == GIT_SUCCESS) {
		map->data = (void *)git_blob_rawcontent(*blob);
		map->len  = git_blob_rawsize(*blob);
	}
	return error;
	git_buf full_path = GIT_BUF_INIT;
	int error = git_buf_joinpath(
		&full_path, git_repository_workdir(repo), file->path);
	if (error != GIT_SUCCESS)
		return error;
		if (map->data == NULL)
			error = GIT_ENOMEM;
		else {
			ssize_t read_len =
				p_readlink(full_path.ptr, map->data, (size_t)file->size + 1);
			if (read_len != (ssize_t)file->size)
				error = git__throw(
					GIT_EOSERR, "Failed to read symlink %s", file->path);
			else
				map->len = read_len;

		}
		error = git_futils_mmap_ro_file(map, full_path.ptr);
	git_buf_free(&full_path);
	int error = GIT_SUCCESS;
		mmfile_t old_xdiff_data, new_xdiff_data;
		error = file_is_binary_by_attr(diff, delta);
		if (error < GIT_SUCCESS)
				error = get_workdir_content(diff->repo, &delta->old_file, &old_data);
					diff->repo, &delta->old_file.oid, &old_data, &old_blob);
			if (error != GIT_SUCCESS)
			(hunk_cb || line_cb || git_oid_iszero(&delta->new_file.oid)) &&
				error = get_workdir_content(diff->repo, &delta->new_file, &new_data);
					diff->repo, &delta->new_file.oid, &new_data, &new_blob);
			if (error != GIT_SUCCESS)
			if ((delta->new_file.flags | GIT_DIFF_FILE_VALID_OID) == 0) {
					&delta->new_file.oid, new_data.data, new_data.len, GIT_OBJ_BLOB);
				if (error != GIT_SUCCESS)
				if (git_oid_cmp(&delta->old_file.oid, &delta->new_file.oid) == 0) {
			if (error < GIT_SUCCESS)
			if (error != GIT_SUCCESS)
		old_xdiff_data.ptr = old_data.data;
		old_xdiff_data.size = old_data.len;
		new_xdiff_data.ptr = new_data.data;
		new_xdiff_data.size = new_data.len;
		xdl_diff(&old_xdiff_data, &new_xdiff_data,
		release_content(&delta->old_file, &old_data, old_blob);
		release_content(&delta->new_file, &new_data, new_blob);
		if (error != GIT_SUCCESS)
		return GIT_SUCCESS;
	old_suffix = pick_suffix(delta->old_file.mode);
	new_suffix = pick_suffix(delta->new_file.mode);
	if (delta->old_file.path != delta->new_file.path &&
		strcmp(delta->old_file.path,delta->new_file.path) != 0)
			delta->old_file.path, old_suffix, delta->new_file.path, new_suffix);
	else if (delta->old_file.mode != delta->new_file.mode &&
		delta->old_file.mode != 0 && delta->new_file.mode != 0)
			delta->old_file.path, new_suffix, delta->old_file.mode, delta->new_file.mode);
		git_buf_printf(pi->buf, "%c\t%s%c\n", code, delta->old_file.path, old_suffix);
		git_buf_printf(pi->buf, "%c\t%s\n", code, delta->old_file.path);
	if (git_buf_lasterror(pi->buf) != GIT_SUCCESS)
		return git_buf_lasterror(pi->buf);
	git_oid_tostr(start_oid, sizeof(start_oid), &delta->old_file.oid);
	git_oid_tostr(end_oid, sizeof(end_oid), &delta->new_file.oid);
	if (delta->old_file.mode == delta->new_file.mode) {
			start_oid, end_oid, delta->old_file.mode);
		if (delta->old_file.mode == 0) {
			git_buf_printf(pi->buf, "new file mode %o\n", delta->new_file.mode);
		} else if (delta->new_file.mode == 0) {
			git_buf_printf(pi->buf, "deleted file mode %o\n", delta->old_file.mode);
			git_buf_printf(pi->buf, "old mode %o\n", delta->old_file.mode);
			git_buf_printf(pi->buf, "new mode %o\n", delta->new_file.mode);
	return git_buf_lasterror(pi->buf);
	int error;
	const char *oldpfx = pi->diff->opts.old_prefix;
	const char *oldpath = delta->old_file.path;
	const char *newpfx = pi->diff->opts.new_prefix;
	const char *newpath = delta->new_file.path;
	git_buf_printf(pi->buf, "diff --git %s%s %s%s\n", oldpfx, delta->old_file.path, newpfx, delta->new_file.path);
	if ((error = print_oid_range(pi, delta)) < GIT_SUCCESS)
		return error;
	if (git_oid_iszero(&delta->old_file.oid)) {
	if (git_oid_iszero(&delta->new_file.oid)) {
	if (git_buf_lasterror(pi->buf) != GIT_SUCCESS)
		return git_buf_lasterror(pi->buf);
	error = pi->print_cb(pi->cb_data, GIT_DIFF_LINE_FILE_HDR, pi->buf->ptr);
	if (error != GIT_SUCCESS || delta->binary != 1)
		return error;
	if (git_buf_lasterror(pi->buf) != GIT_SUCCESS)
		return git_buf_lasterror(pi->buf);
	if (git_buf_printf(pi->buf, "%.*s", (int)header_len, header) == GIT_SUCCESS)
		return pi->print_cb(pi->cb_data, GIT_DIFF_LINE_HUNK_HDR, pi->buf->ptr);
	else
		return git_buf_lasterror(pi->buf);
	if (git_buf_lasterror(pi->buf) != GIT_SUCCESS)
		return git_buf_lasterror(pi->buf);
	mmfile_t old_data, new_data;
		old_data.ptr  = (char *)git_blob_rawcontent(old_blob);
		old_data.size = git_blob_rawsize(old_blob);
		old_data.ptr  = "";
		old_data.size = 0;
		new_data.ptr  = (char *)git_blob_rawcontent(new_blob);
		new_data.size = git_blob_rawsize(new_blob);
		new_data.ptr  = "";
		new_data.size = 0;
	delta.status = old_data.ptr ?
		(new_data.ptr ? GIT_DELTA_MODIFIED : GIT_DELTA_DELETED) :
		(new_data.ptr ? GIT_DELTA_ADDED : GIT_DELTA_UNTRACKED);
	delta.old_file.mode = 0100644; /* can't know the truth from a blob alone */
	delta.new_file.mode = 0100644;
	git_oid_cpy(&delta.old_file.oid, git_object_id((const git_object *)old_blob));
	git_oid_cpy(&delta.new_file.oid, git_object_id((const git_object *)new_blob));
	delta.old_file.path = NULL;
	delta.new_file.path = NULL;
	xdl_diff(&old_data, &new_data, &xdiff_params, &xdiff_config, &xdiff_callback);
	return GIT_SUCCESS;