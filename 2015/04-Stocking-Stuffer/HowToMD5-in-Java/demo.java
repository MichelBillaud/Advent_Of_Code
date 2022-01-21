import java.security.MessageDigest;

System.out.println("Hello");

String string = "abcdef609043";

MessageDigest md = MessageDigest.getInstance("MD5");
  
md.update(string.getBytes());
byte[] digest = md.digest();

System.out.println("String: " + string);
System.out.print("Digest: ");
for (var b : digest) {
	System.out.format("%02x", b);
}
System.out.println();


