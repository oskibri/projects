#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>


#define BUFFER_SIZE 65536

int download_file(ssh_session sess, const char *rfile, const char *lfile) {
	sftp_session sftp;
	sftp_file file;
	int rc, ffd;
	char buffer[65536];
	ssize_t nwritten, nread;

	sftp = sftp_new(sess);
	rc = sftp_init(sftp);
	file = sftp_open(sftp, rfile, O_RDONLY, 0);

	ffd = open(lfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	while ((nread = sftp_read(file, buffer, sizeof(buffer))) > 0) {
		nwritten = write(ffd, buffer, nread);
		printf("Numbers written to local file: %zd\n", nwritten);
	}


	if (nread < 0) {
		fprintf(stderr, "Error reading from remote file\n");
	}

	close(ffd);
	sftp_close(file);
	sftp_free(sftp);

	return SSH_OK;
}

int execute_cmd(ssh_session sess, const char *cmd) {
	ssh_channel chan;
	int rc;
	char buffer[BUFFER_SIZE];
	int nbytes;

	// create a new channel
	chan = ssh_channel_new(sess);
	
	// open a session on the channel
	rc = ssh_channel_open_session(chan);

	// execute command
	rc = ssh_channel_request_exec(chan, cmd);
	nbytes = ssh_channel_read(chan, buffer, sizeof buffer, 0);
	while (nbytes > 0) {
		fwrite(buffer, 1, nbytes, stdout);
		fflush(stdout);
		nbytes = ssh_channel_read(chan, buffer, sizeof buffer, 0);
	}

	if (nbytes < 0) {
		fprintf(stderr, "Error reading from channel\n");
	}

	// close and free the channel
	ssh_channel_send_eof(chan);
	ssh_channel_close(chan);
	ssh_channel_free(chan);

	return SSH_OK;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <remote_file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	ssh_session sess = ssh_new();
	if (sess == NULL) {
		fprintf(stderr, "Error createing SSH session\n");
		return EXIT_FAILURE; 
	}

	int yes=1;

	/// set option for SSH connection
	ssh_options_set(sess, SSH_OPTIONS_HOST, "elinor-osl.servebolt.cloud");
	ssh_options_set(sess, SSH_OPTIONS_USER, "oskarhesle");
	ssh_options_set(sess, SSH_OPTIONS_IDENTITY, "/home/oskar/.ssh/servebolt");
	ssh_options_set(sess, SSH_OPTIONS_COMPRESSION, "yes");
	ssh_options_set(sess, SSH_OPTIONS_NODELAY, &yes);
	
	// connect to the server
	int rc = ssh_connect(sess);
	if (rc != SSH_OK) {
		fprintf(stderr, "Error connecting to host: %s\n", ssh_get_error(sess));
		ssh_free(sess);
		return EXIT_FAILURE;
	}

	// authenticate using ssh keys
	// char* privkey = "/home/oskar/.ssh/id_ed25519";
	rc = ssh_userauth_publickey_auto(sess, NULL, NULL);
	if (rc != SSH_AUTH_SUCCESS) {
		fprintf(stderr, "Authentication failed: %s\n", ssh_get_error(sess));
		ssh_disconnect(sess);
		ssh_free(sess);
		return EXIT_FAILURE;
	}

	printf("Connected and authenticated to the SSH server!\n");

	//rc = execute_cmd(sess, "ls -lah");
	//if (rc != SSH_OK) {
	//	fprintf(stderr, "Failed to execute remote command\n");
	//}

	rc = download_file(sess, argv[1], "local.txt");
	if (rc != SSH_OK) {
		fprintf(stderr, "Failed to download remote file\n");
	}

	ssh_disconnect(sess);
	ssh_free(sess);
	
	return EXIT_SUCCESS;
}
