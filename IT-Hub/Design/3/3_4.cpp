#include "../../../include/utils.h"
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

struct Node {
  int timestamp;
  int tweetId;
  int userId;
  int index;
  bool operator<(const Node &other) const {
    return timestamp < other.timestamp;
  }
};

class Twitter {
  // tweets[userId] -> {(timestamp, tweetId), ...} most recent on the back
  std::unordered_map<int, std::vector<std::pair<int, int>>> tweets;
  // following[userId] -> set of users that userId follows
  std::unordered_map<int, std::unordered_set<int>> following;
  // timestamp / counter
  int timestamp = 0;

public:
  void postTweet(int userId, int tweetId) {
    tweets[userId].push_back({timestamp, tweetId});
    timestamp++;
  }

  void follow(int followerId, int followeeId) {
    following[followerId].insert(followeeId);
  }

  void unfollow(int followerId, int followeeId) {
    if (auto it = following.find(followerId); it != following.end())
      it->second.erase(followeeId);
  }

  std::optional<Node> getBackNode(int userId) {
    if (auto it = tweets.find(userId);
        it != tweets.end() && !it->second.empty()) {
      Node node;
      node.userId = userId;
      node.index = it->second.size() - 1;
      node.timestamp = it->second[node.index].first;
      node.tweetId = it->second[node.index].second;
      return node;
    }
    return std::nullopt;
  }

  Node getMostRecentNode(std::unordered_map<int, Node> &nodes) {
    Node bestNode;
    bestNode.timestamp = -1;

    for (auto [timestamp, node] : nodes)
      if (timestamp > bestNode.timestamp)
        bestNode = node;

    return bestNode;
  }

  std::vector<int> getNewsFeed(int userId) {
    // nodes[timestamp] = node
    std::unordered_map<int, Node> nodes;

    // user's own tweets
    if (auto node = getBackNode(userId); node.has_value())
      nodes.insert({node->timestamp, *node});

    // Tweets from followed users
    if (auto it = following.find(userId); it != following.end())
      for (int followeeId : it->second)
        if (auto node = getBackNode(followeeId); node.has_value())
          nodes.insert({node->timestamp, *node});

    std::vector<int> feed;
    feed.reserve(10);

    while (!nodes.empty() && feed.size() < 10) {
      Node node = getMostRecentNode(nodes);
      nodes.erase(node.timestamp);

      feed.push_back(node.tweetId);

      // move to this user's next-most-recent tweet
      if (node.index > 0) {
        node.index--;
        node.timestamp = tweets[node.userId][node.index].first;
        node.tweetId = tweets[node.userId][node.index].second;
        nodes.insert({node.timestamp, node});
      }
    }

    return feed;
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
