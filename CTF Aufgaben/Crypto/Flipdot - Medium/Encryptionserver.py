from Crypto.Cipher import AES
from Crypto.Util.Padding import pad,unpad
from Crypto.Random import get_random_bytes
from binascii import unhexlify
import socketserver 
import socket, os


FLAG = 'nflag{dummy-flag-for-testing}'

key = get_random_bytes(16)
iv = get_random_bytes(16)


def encrypt_data(data):
	padded = pad(data.encode(),16,style='pkcs7')
	cipher = AES.new(key, AES.MODE_CBC,iv)
	enc = cipher.encrypt(padded)
	return enc.hex()

def decrypt_data(encryptedParams):
	cipher = AES.new(key, AES.MODE_CBC,iv)
	paddedParams = cipher.decrypt( unhexlify(encryptedParams))
	print(paddedParams)
	if b'root&password=password123' in unpad(paddedParams,16,style='pkcs7'):
		return 1
	else:
		return 0

def send_msg(s, msg):
	enc = msg.encode()
	s.send(enc)

def login(s):
	send_msg(s,'\nLogin with auth ciphertext: ')

	enc_msg = s.recv(4096).decode().strip()
	
	try:
		check = decrypt_data(enc_msg)
	except Exception as e:
		send_msg(s, str(e) + '\n')
		s.close()

	if check:
		send_msg(s, '\nLogged in! \n'+ FLAG)
		s.close()
	else:
		send_msg(s, 'Auth ciphertext is incorrect!\n')
		s.close()
		
def createAuth(s):
	send_msg(s, '\nUsername: ')
	user = s.recv(4096).decode().strip()

	send_msg(s, 'Password: ' )
	passwd = s.recv(4096).decode().strip()

	msg = 'username=' + user +'&password=' + passwd

	try:
		assert('username=root&password=password123' not in msg)
	except AssertionError:
		send_msg(s, 'Good try but we are security experts!\n')
		return
		raise

	msg = 'auth:  username=' + user +'&password=' + passwd
	send_msg(s, 'Auth ciphertext: ' + encrypt_data(msg)+'\n')
	return

def main(s):

	for i in range(0,3):
		send_msg(s, '\nMenue: \n [1] Create your own Auth ciphertext \n [2] Log into server\n Choose: ')
		menue = s.recv(4096).decode().strip()

		if(menue=='1'):
			createAuth(s)
		elif(menue=='2'):
			login(s)
		else:
			print('Error! Give input of numbers from 1 or 2\n')
		
		


class TaskHandler(socketserver.BaseRequestHandler):
	def handle(self):
		main(self.request)

if __name__ == '__main__':
	socketserver.ThreadingTCPServer.allow_reuse_address = True
	server = socketserver.ThreadingTCPServer(('0.0.0.0', 1337), TaskHandler)
	server.serve_forever()