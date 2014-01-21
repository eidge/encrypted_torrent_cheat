encrypted_torrent_cheat
=======================

Encrypting the torrent protocol is not a viable way of guaranteeing that a user can not cheat his racio. 

This proof-of-concept let's you save and intercept requests from your bittorrent client to the tracker and vice-versa.

# How to cheat the tracker?

 0- In your hosts file, route all connections from the trackers domain to localhost.
 1- Open up your bittorrent program.
 2- Add a new torrent.
 3- Save the first outcoming request to the tracker (Even though the data is encrypted you know it will tell the tracker you haven't downloaded any parts yet - because you haven't)
 4- Each time the bittorrent program wants to send data to the tracker drop it and send the first request you saved.
 5- The tracker will never know how much data you've downloaded.
 
# Why is this program not automatic?

 This is a proof-of-concept. If you want to use bittorrent, seed!
 
 The sole purpose of this application is demonstrate that security by obscurity is not a good solution.

# This doesn't work

 Well this is a proof-of-concept. It's imcomplete on purpose, I don't like cheater, no one likes cheaters.
 
 It should ring a bell though.

# Motivation behind this application

  I used a portuguese bittorrent comunity that used a lazy closed source bittorrent application with no version for linux.
  
  I offered to port the thing. They said no because it was a security hazard that might bring potential cheaters.
  
  **Well there's no need to have the source code to cheat when the underlying protocol wasn't meant to be secure.**
