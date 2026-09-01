#include "../../../include/utils.h"
#include <ostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Twitter {
  // tweets[i] -> {userId, tweetId} most recent on the back
  std::vector<std::pair<int, int>> tweets;
  // following[userId] -> set of users that userId follows
  std::unordered_map<int, std::unordered_set<int>> following;

public:
  void postTweet(int userId, int tweetId) {
    tweets.push_back({userId, tweetId});
  }

  void follow(int followerId, int followeeId) {
    if (following.count(followerId) == 0)
      following[followerId] = {};
    // ignore if followeeId already exists
    following[followerId].insert(followeeId);
  }

  void unfollow(int followerId, int followeeId) {
    if (following.count(followerId) == 1)
      // ignore if followeeId does not exist
      following[followerId].erase(followeeId);
  }

  std::vector<int> getNewsFeed(int userId) {
    std::vector<int> newsFeed;
    newsFeed.reserve(10);
    bool hasFollowers = following.count(userId);
    for (int i = tweets.size() - 1, count = 0; i >= 0 && count < 10; i--) {
      auto [poster, tweetId] = tweets[i];
      if (poster == userId ||
          (hasFollowers && following[userId].count(poster))) {
        newsFeed.push_back(tweetId);
        count++;
      }
    }
    return newsFeed;
  }

  void printTweets() {
    std::cout << "{";
    for (int i = 0; i < tweets.size(); i++) {
      if (i != 0)
        std::cout << ", ";
      std::cout << tweets[i].first << ": " << tweets[i].second;
    }
    std::cout << "}";
  }
};

int main() {
  printTitle("Design Twitter");
  std::cout << "Solution:" << std::endl;

  Twitter myTwitter = Twitter();
  std::vector<std::string> methods = {
      "postTweet", "postTweet",  "postTweet",   "postTweet", "postTweet",
      "postTweet", "postTweet",  "postTweet",   "postTweet", "postTweet",
      "postTweet", "postTweet",  "postTweet",   "postTweet", "postTweet",
      "postTweet", "postTweet",  "postTweet",   "postTweet", "postTweet",
      "postTweet", "postTweet",  "getNewsFeed", "follow",    "getNewsFeed",
      "unfollow",  "getNewsFeed"};
  std::vector<std::vector<int>> parameters = {
      {1, 5},   {2, 3},   {1, 101}, {2, 13},  {2, 10},  {1, 2},   {1, 94},
      {2, 505}, {1, 333}, {2, 22},  {1, 11},  {1, 205}, {2, 203}, {1, 201},
      {2, 213}, {1, 200}, {2, 202}, {1, 204}, {2, 208}, {2, 233}, {1, 222},
      {2, 211}, {1},      {1, 2},   {1},      {1, 2},   {1}};
  for (int i = 0; i < methods.size(); i++) {
    if (methods[i] == "postTweet")
      myTwitter.postTweet(parameters[i][0], parameters[i][1]);
    else if (methods[i] == "follow")
      myTwitter.follow(parameters[i][0], parameters[i][1]);
    else if (methods[i] == "unfollow")
      myTwitter.unfollow(parameters[i][0], parameters[i][1]);
    else if (methods[i] == "getNewsFeed")
      printVector(myTwitter.getNewsFeed(parameters[i][0]));
  }

  return 0;
}
