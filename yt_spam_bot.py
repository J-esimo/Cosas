from selenium import webdriver
import time
import random

email = "email@gmail.com"
passwd = "strongest_password"


def do_spam(times: int, nvideos: int, msg: str, start_url: str):
    driver = webdriver.Chrome()
    driver.get(
        "https://accounts.google.com/o/oauth2/auth/identifier?client_id=717762328687-iludtf96g1hinl76e4lc1b9a82g457nn.apps.googleusercontent.com&scope=profile%20email&redirect_uri=https%3A%2F%2Fstackauth.com%2Fauth%2Foauth2%2Fgoogle&state=%7B%22sid%22%3A1%2C%22st%22%3A%2259%3A3%3Abbc%2C16%3Acfb8ea917b7980a6%2C10%3A1602553366%2C16%3A46e047074b1428bd%2C139463c1a167371baa639ad8d8ecfc3a94746fd8bda7b02accd8d3eafdf28d31%22%2C%22cdl%22%3Anull%2C%22cid%22%3A%22717762328687-iludtf96g1hinl76e4lc1b9a82g457nn.apps.googleusercontent.com%22%2C%22k%22%3A%22Google%22%2C%22ses%22%3A%222262f36de9a74f7e9b51db52b7c222b2%22%7D&response_type=code&flowName=GeneralOAuthFlow")
    email_ = driver.find_element_by_name("identifier")
    email_.clear()
    email_.send_keys(email)
    driver.find_element_by_class_name("VfPpkd-RLmnJb").click()
    time.sleep(5)
    passwd_ = driver.find_element_by_name("password")
    passwd_.clear()
    passwd_.send_keys(passwd)
    driver.find_element_by_class_name("VfPpkd-RLmnJb").click()
    driver.get(start_url)
    time.sleep(2)
    for _ in range(nvideos):
        time.sleep(2)
        driver.execute_script("window.scrollTo(0, 500);")
        for _ in range(times):
            time.sleep(1)
            comment_box = driver.find_element_by_id('placeholder-area')
            comment_box.click()
            input_box = driver.find_element_by_id('contenteditable-root')
            input_box.send_keys(msg)
            driver.find_element_by_xpath(
                "//paper-button[@class='style-scope ytd-button-renderer style-primary size-default']").click()
        time.sleep(1)
        videos = driver.find_elements_by_xpath(
            '//*[@class="yt-simple-endpoint style-scope ytd-compact-video-renderer"]')
        random_video = random.choice(videos)
        driver.get(random_video.get_attribute("href"))


# Example
do_spam(2, 3, "Nice video, +1 sub", "https://www.youtube.com/watch?v=v3fQqjqYPJA&ab_channel=Methalodon")
